#include "Enemy/HexagonStage.h"
#include "framework/World.h"
#include "Enemy/Hexagon.h"

namespace ly
{
    HexagonStage::HexagonStage(World* world_)
        : GameStage{world_},
        mSpawnInterval{5.f},
        mSideSpawnOffset{80.f},
        mSpawnGroupAmt{5},
        mCurrentSpawnCount{0},
        mMidSpawnLoc{world_->GetWindowSize().x / 2.f, -100.f},
        mRightSpawnLoc{world_->GetWindowSize().x / 2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset},
        mLeftSpawnLoc{world_->GetWindowSize().x / 2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset}
    {}

    void HexagonStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
    }
    
    void HexagonStage::SpawnHexagon()
    {
        weak<Hexagon> _newHexagon = GetWorld()->SpawnActor<Hexagon>();
        _newHexagon.lock()->SetActorLocation(mMidSpawnLoc);

        _newHexagon = GetWorld()->SpawnActor<Hexagon>();
        _newHexagon.lock()->SetActorLocation(mLeftSpawnLoc);
        _newHexagon = GetWorld()->SpawnActor<Hexagon>();
        _newHexagon.lock()->SetActorLocation(mRightSpawnLoc);

        if(++mCurrentSpawnCount == mSpawnGroupAmt)
        {
            FinishStage();
        }

    }

    void HexagonStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    
} // namespace ly
