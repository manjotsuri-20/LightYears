#pragma once

#include "framework/Actor.h"
#include "gameplay/GameStage.h"

namespace ly
{
    class BossStage : public GameStage
    {
        public:
            BossStage(World* world_);
            virtual void StartStage() override;

        private:
            void BossDestroyed(Actor* bossActor_);
    };
}  // namespace ly
