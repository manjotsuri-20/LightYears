#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly
{
    GameStage::GameStage(World* world_)
        : mWorld{world_},
        mStageFinished{false}
    {}

    void GameStage::StartStage()
    {
        LOG("Stage Started");
    }

    void GameStage::TickStage(float deltaTime_)
    {
        // LOG("Stage Ticking");
    }

    void GameStage::FinishStage()
    {
        onStageFinished.Broadcast();
        mStageFinished = true;
        StageFinished();
    }

    void GameStage::StageFinished()
    {
        LOG("Stage Finished");
    }

} // namespace ly
