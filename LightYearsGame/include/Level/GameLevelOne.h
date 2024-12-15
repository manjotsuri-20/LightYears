#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class HUD;
    class GameLevelOne : public World
    {
        public:
            GameLevelOne(Application* ownningApp);
            void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);

        private:
            void GameOver();
            weak<PlayerSpaceship> mPlayerSpaceship;
            weak<HUD> mGameplayHUD;
            virtual void BeginPlay() override;
            virtual void InitGameStages() override;

    };
} // namespace ly
