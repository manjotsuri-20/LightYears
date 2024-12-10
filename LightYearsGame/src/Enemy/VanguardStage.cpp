#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/World.h"

namespace ly
{
    VanguardStage::VanguardStage(World* world_)
        : GameStage{world_},
        mSpawnInterval{1.5f},
        mSwitchInterval{5.f},
        mSpawnDistanceToEdge{100.f},
        mLeftSpawnLoc{0.0f, 0.0f},
        mRightSpawnLoc{0.0f, 0.0f},
        mSpawnLoc{0.0f, 0.0f},
        mRowsToSpawn{2},
        mRowSpawnCount{0},
        mVanguardsPerRow{5},
        mCurrentRowVanguardCount{0}
    {}

    void VanguardStage::StartStage()
    {
        auto windowSize_ = GetWorld()->GetWindowSize();
        mLeftSpawnLoc = sf::Vector2f{mSpawnDistanceToEdge, -100.f};
        mRightSpawnLoc = sf::Vector2f{windowSize_.x - mSpawnDistanceToEdge, -100.f};

        SwitchRow();
    }
    
    void VanguardStage::SpawnVanguard()
    {
        weak<Vanguard> _newVanguard = GetWorld()->SpawnActor<Vanguard>();
        _newVanguard.lock()->SetActorLocation(mSpawnLoc);
        _newVanguard.lock()->SetActorRotation(90.f);
        ++mCurrentRowVanguardCount;

        if(mCurrentRowVanguardCount == mVanguardsPerRow)
        {
            TimerManager::Get().ClearTimer(mSpawnTimerHandle);
            mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
            mCurrentRowVanguardCount = 0;
        }
    }
    
    void VanguardStage::SwitchRow()
    {
        if(mRowSpawnCount == mRowsToSpawn)
        {
            FinishStage();
            return;
        }

        if(mSpawnLoc == mLeftSpawnLoc)
        {
            mSpawnLoc = mRightSpawnLoc;
        }
        else
        {
            mSpawnLoc = mLeftSpawnLoc;
        }

        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

        ++mRowSpawnCount;
    }

    void VanguardStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
        TimerManager::Get().ClearTimer(mSwitchTimerHandle);
    }
} // namespace ly
