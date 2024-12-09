#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <functional>

namespace ly
{
    struct TimerHandle
    {
        public:
            TimerHandle();
            unsigned int GetTimerKey() const { return mTimerKey; }

        private:
            unsigned int mTimerKey;
            static unsigned int timerKeyCounter;
            static unsigned int GetNextTimerKey() { return ++timerKeyCounter; }
    };

    struct TimerHandleHashFunction
    {
        public:
            std::size_t operator()(const TimerHandle& timerHandle_) const
            {
                return timerHandle_.GetTimerKey();
            }
    };

    bool operator==(const TimerHandle& lhs_, const TimerHandle& rhs_);

    struct Timer
    {
        public:
            Timer(weak<Object> weakRef_, std::function<void()> callback_, float duration_, float repeat_);
            void TickTime(float deltaTime_);
            bool Expired() const;
            void SetExpired();
        private:
            std::pair<weak<Object>, std::function<void()>> mListener;
            float mDuration;
            float mRepeat;
            float mTimeCounter;
            bool mIsExpired;
    };

    class TimerManager
    {
        public:
            static TimerManager& Get();

            template<typename ClassName>
            TimerHandle SetTimer(weak<Object> weakRef_, void(ClassName::*callback_)(), float duration_, bool repeat_ = false)
            {
                TimerHandle newHandle_{};
                mTimers.insert({newHandle_, Timer(weakRef_, [=]{(static_cast<ClassName*>(weakRef_.lock().get())->*callback_)();}, duration_, repeat_)});
                return newHandle_;
            }

            void UpdateTimer(float deltaTime_);
            void ClearTimer(TimerHandle timerHandle_);

        protected:
            TimerManager();

        private:
            static unique<TimerManager> mTimerManager;
            Dictionary<TimerHandle, Timer, TimerHandleHashFunction> mTimers;

    };
} // namespace ly
