#pragma once
#include "gameplay/GameStage.h"

namespace ly
{
    class WaitStage : public GameStage
    {
        public:
            WaitStage(World* world_, float waitDuration_ = 5.f);
            virtual void StartStage() override;

        private:
            float mWaitDuration;
    };
} // namespace ly
