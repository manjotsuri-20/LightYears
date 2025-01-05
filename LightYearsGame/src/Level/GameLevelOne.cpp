#include "Level/GameLevelOne.h"

#include "Enemy/BossStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "SFML/Graphics/Color.hpp"
#include "framework/Application.h"
#include "framework/BackdropActor.h"
#include "framework/BackgroundLayer.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {
    }

    void GameLevelOne::BeginPlay()
    {
        SpawnCosmetics();
        Player& _newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = _newPlayer.SpawnPlayerSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        mGameplayHUD = SpawnHUD<GameplayHUD>();
        mGameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::RestartGame);
        mGameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnPlayerSpaceship(this);
        if (!mPlayerSpaceship.expired())
        {
            mPlayerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<UFOStage>{new UFOStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<ChaosStage>{new ChaosStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<BossStage>{new BossStage{this}});
    }

    void GameLevelOne::GameOver()
    {
        LOG("GameOver");
        mGameplayHUD.lock()->GameFinished(false);
    }

    void GameLevelOne::AllGameStageFinished()
    {
        mGameplayHUD.lock()->GameFinished(true);
    }

    void GameLevelOne::RestartGame()
    {
        PlayerManager::Get().Reset();
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void GameLevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }

    void GameLevelOne::SpawnCosmetics()
    {
        auto _backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");

        weak<BackgroundLayer> _planets = SpawnActor<BackgroundLayer>();
        _planets.lock()->SetAssets({
            "SpaceShooterRedux/PNG/Planets/Planet1.png",
            "SpaceShooterRedux/PNG/Planets/Planet2.png",
            "SpaceShooterRedux/PNG/Planets/Planet3.png",
            "SpaceShooterRedux/PNG/Planets/planet4.png",
            "SpaceShooterRedux/PNG/Planets/planet5.png",
            "SpaceShooterRedux/PNG/Planets/planet6.png",
            "SpaceShooterRedux/PNG/Planets/planet7.png",
        });

        _planets.lock()->SetSpriteCount(1);
        _planets.lock()->SetSizes(1.0f, 1.5f);
        _planets.lock()->SetVelocities({0.f, 30.f}, {0, 80.f});

        weak<BackgroundLayer> _meteors = SpawnActor<BackgroundLayer>();
        _meteors.lock()->SetAssets({
            "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
			"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
        });

        _meteors.lock()->SetSpriteCount(20);
        _meteors.lock()->SetSizes(0.2f, 0.5f);
    }
}  // namespace ly
