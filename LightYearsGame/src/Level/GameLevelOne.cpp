#include "Level/GameLevelOne.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/WaitStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {}

    void GameLevelOne::BeginPlay()
    {
        Player& _newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = _newPlayer.SpawnPlayerSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
        mGameplayHUD = SpawnHUD<GameplayHUD>();
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnPlayerSpaceship(this);
        if(!mPlayerSpaceship.expired())
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
    }

    void GameLevelOne::GameOver()
    {
        LOG("GameOver");
    }
    
} // namespace ly

