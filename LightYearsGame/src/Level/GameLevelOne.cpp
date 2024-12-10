#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        // testPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        // testPlayerSpaceship.lock()->SetActorRotation(-90.f);

    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
    }
} // namespace ly

