#include "Level/MainMenuLevel.h"

#include "Level/GameLevelOne.h"
#include "framework/Application.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
    MainMenuLevel::MainMenuLevel(Application* owningApplication_)
        : World{owningApplication_}
    {
        mMainMenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenuLevel::BeginPlay()
    {
        mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
        mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
    }

    void MainMenuLevel::StartGame()
    {
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void MainMenuLevel::QuitGame()
    {
        GetApplication()->QuitApplication();
    }
}  // namespace ly
