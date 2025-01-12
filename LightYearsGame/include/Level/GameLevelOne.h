#pragma once
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "widgets/GameplayHUD.h"

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
            weak<GameplayHUD> mGameplayHUD;
            virtual void BeginPlay() override;
            virtual void InitGameStages() override;
            virtual void AllGameStageFinished() override;
            void RestartGame();
            void QuitGame();
            void SpawnCosmetics();
            void PauseGame();
    };
}  // namespace ly
