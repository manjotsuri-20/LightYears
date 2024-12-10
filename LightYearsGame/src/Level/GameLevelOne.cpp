#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/WaitStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(-90.f);

    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
    }
} // namespace ly

