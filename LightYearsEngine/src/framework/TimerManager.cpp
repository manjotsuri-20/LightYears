#include "framework/TimerManager.h"

namespace ly
{
    unsigned int TimerHandle::timerKeyCounter = 0;

    TimerHandle::TimerHandle()
        : mTimerKey(GetNextTimerKey())
    {}

    bool operator==(const TimerHandle& lhs_, const TimerHandle& rhs_)
    {
        return lhs_.GetTimerKey() == rhs_.GetTimerKey();
    }

    Timer::Timer(weak<Object> weakRef_, std::function<void()> callback_, float duration_, float repeat_)
        : mListener{weakRef_, callback_},
        mDuration{duration_},
        mRepeat{repeat_},
        mTimeCounter{0},
        mIsExpired{false}
    {
        
    }

    void Timer::TickTime(float deltaTime_)
    {
        if(Expired())
        {
            return;
        }

        mTimeCounter += deltaTime_;
        if(mTimeCounter >= mDuration)
        {
            mListener.second();
            if(mRepeat)
            {
                mTimeCounter = 0;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }

    unique<TimerManager> TimerManager::mTimerManager{nullptr};

    TimerManager::TimerManager()
    {
    }

    TimerManager& TimerManager::Get()
    {
        if(!mTimerManager)
        {
            mTimerManager = unique<TimerManager>(new TimerManager{});
        }
        return *mTimerManager;
    }

    void TimerManager::UpdateTimer(float deltaTime_)
    {
        for(auto iter_ = mTimers.begin(); iter_ != mTimers.end();)
        {
            if(iter_->second.Expired())
            {
                iter_ = mTimers.erase(iter_);
            }
            else
            {
                iter_->second.TickTime(deltaTime_);
                iter_++;
            }
        }
    }

    void TimerManager::ClearTimer(TimerHandle timerHandle_)
    {
        auto iter_ = mTimers.find(timerHandle_);
        if(iter_ != mTimers.end())
        {
            iter_->second.SetExpired();
        }
    }


} // namespace ly

