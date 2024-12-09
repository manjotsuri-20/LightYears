#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "spaceship/Spaceship.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application{600, 900, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<World> newWorld = LoadWorld<World>();
        // newWorld.lock()->SpawnActor<Actor>();
        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        // testPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        // testPlayerSpaceship.lock()->SetActorRotation(-90.f);

        weak<Spaceship> _testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
        _testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        _testSpaceship.lock()->SetActorLocation(sf::Vector2f{100.f, 50.f});
        _testSpaceship.lock()->SetTeamID(2);
        counter = 0.f;
    }

    void GameApplication::Tick(float deltaTime_)
    {
        counter += deltaTime_;
        // if(counter > 10.f)
        // {
        //     if(!testPlayerSpaceship.expired())
        //     {
        //         testPlayerSpaceship.lock()->Destroy();
        //     }
        // }
    }

    GameApplication::~GameApplication()
    {
        LOG("Game Application destroyed");
    }
}