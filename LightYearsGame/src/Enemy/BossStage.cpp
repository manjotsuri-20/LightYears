#include "Enemy/BossStage.h"

#include "Enemy/Boss.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"

namespace ly
{
    BossStage::BossStage(World* world_)
        : GameStage(world_)
    {
    }

    void BossStage::StartStage()
    {
        weak<Boss> _newBoss = GetWorld()->SpawnActor<Boss>();
        auto _windowSize = GetWorld()->GetWindowSize();
        _newBoss.lock()->SetActorLocation({_windowSize.x / 2.f, 200.f});
        _newBoss.lock()->onActorDestroy.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
    }

    void BossStage::BossDestroyed(Actor* bossActor_)
    {
        FinishStage();
    }
}  // namespace ly
