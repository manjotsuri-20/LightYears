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
        newWorld.lock()->SpawnActor<Actor>();
        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        // testPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        // testPlayerSpaceship.lock()->SetActorRotation(-90.f);
        testPlayerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
        counter = 0;
    }

    void GameApplication::Tick(float deltaTime_)
    {
        // counter += deltaTime_;
        // if(counter > 2.f)
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