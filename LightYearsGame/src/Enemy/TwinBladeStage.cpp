#include "Enemy/TwinBladeStage.h"
#include "Enemy/TwinBlade.h"

namespace ly
{
    TwinBladeStage::TwinBladeStage(World* world_)
        : GameStage{world_},
        mSpawnInterval{1.5f},
        mSpawnDistanceToCentre{100.f},
        mLeftSpawnLoc{world_->GetWindowSize().x/2.f - mSpawnDistanceToCentre, -100.f},
        mRightSpawnLoc{world_->GetWindowSize().x/2.f + mSpawnDistanceToCentre, -100.f},
        mSpawnLoc{mLeftSpawnLoc},
        mSpawnAmt{10},
        mCurrentSpawnCount{0}
    {}

    void TwinBladeStage::StartStage()
    {
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        weak<TwinBlade> _newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        _newTwinBlade.lock()->SetActorLocation(mSpawnLoc);
        if(mSpawnLoc == mLeftSpawnLoc)
        {
            mSpawnLoc = mRightSpawnLoc;
        }
        else
        {
            mSpawnLoc = mLeftSpawnLoc;
        }

        ++mCurrentSpawnCount;

        if(mCurrentSpawnCount == mSpawnAmt)
        {
            FinishStage();
        }
    }

    void TwinBladeStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
    }


} // namespace ly
