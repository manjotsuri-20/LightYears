#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameLevelOne : public World
    {
        public:
            GameLevelOne(Application* ownningApp);

        private:
            weak<PlayerSpaceship> testPlayerSpaceship;
            virtual void BeginPlay() override;
            virtual void InitGameStages() override;

    };
} // namespace ly
