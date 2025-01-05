#include "Level/MainMenuLevel.h"

#include "Level/GameLevelOne.h"
#include "SFML/System/Vector2.hpp"
#include "framework/Application.h"
#include "framework/BackdropActor.h"
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

        SpawnActor<BackdropActor>("SpaceShooterRedux/mainMenuBg.png", sf::Vector2f{0.f, 0.f});
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
