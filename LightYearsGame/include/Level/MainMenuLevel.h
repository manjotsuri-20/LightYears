#pragma once

#include "framework/Application.h"
#include "framework/World.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
    class MainMenuHUD;
    class MainMenuLevel : public World
    {
        public:
            MainMenuLevel(Application* owningApplication_);
            virtual void BeginPlay() override;

        private:
            weak<MainMenuHUD> mMainMenuHUD;
            void StartGame();
            void QuitGame();
    };

}  // namespace ly
