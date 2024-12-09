#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        // testPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        // testPlayerSpaceship.lock()->SetActorRotation(-90.f);

        weak<Vanguard> _testSpaceship = SpawnActor<Vanguard>();
        // _testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        _testSpaceship.lock()->SetActorLocation(sf::Vector2f{100.f, 50.f});

    }

    void GameLevelOne::BeginPlay()
    {
        timerIndex_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 1, true);
    }

    void ly::GameLevelOne::TimerCallback_Test()
    {
        LOG("Callback called!");
        // TimerManager::Get().ClearTimer(timerIndex_Test);
    }
} // namespace ly

