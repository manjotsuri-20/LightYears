#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    WaitStage::WaitStage(World* world_, float waitDuration_)
        : GameStage{world_},
        mWaitDuration{waitDuration_}
    {}

    void WaitStage::StartStage()
    {
        TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, mWaitDuration, false);
    }
} // namespace ly

