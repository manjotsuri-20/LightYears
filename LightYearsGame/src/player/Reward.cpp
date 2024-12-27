#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/World.h"
#include "player/PlayerManager.h"

namespace ly
{
    Reward::Reward(World *world_, const std::string &texturePath_, RewardFunc rewardFunction_, float speed_)
        : Actor{world_, texturePath_},
        mRewardFunc{rewardFunction_},
        mSpeed{speed_}
    {
    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Reward::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);
        AddActorLocationOffset({0.f, mSpeed * deltaTime_});
    }

    void Reward::OnActorBeginOverlap(Actor *otherActor_)
    {
        if(!otherActor_ || otherActor_->IsPendingDestroy())
            return;

        if(!PlayerManager::Get().GetPlayer())
            return;

        weak<PlayerSpaceship> _playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();
        if(_playerSpaceship.expired() || _playerSpaceship.lock()->IsPendingDestroy())
            return;

        if(_playerSpaceship.lock()->GetUniqueId() == otherActor_->GetUniqueId())
        {
            mRewardFunc(_playerSpaceship.lock().get());
            Destroy();
        }
    }

    weak<Reward> CreateHealthReward(World* world_)
    {
        return CreateReward(world_, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
    }

    weak<Reward> CreateThreeWayShooterReward(World* world_)
    {
        return CreateReward(world_, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
    }

    weak<Reward> CreateFrontalWiperReward(World* world_)
    {
        return CreateReward(world_, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
    }

    weak<Reward> CreateLifeReward(World *world_)
    {
        return CreateReward(world_, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLife);
    }

    weak<Reward> CreateReward(World* world_, const std::string& texturePath_, RewardFunc rewardFunc_)
    {
        weak<Reward> _reward = world_->SpawnActor<Reward>(texturePath_, rewardFunc_);
        return _reward;
    }

    void RewardHealth(PlayerSpaceship *player_)
    {
        static float _rewardAmt = 10.f;
        if(player_ != nullptr && !player_->IsPendingDestroy())
        {
            player_->GetHealthComp().ChangeHealth(_rewardAmt);
        }
    }

    void RewardThreeWayShooter(PlayerSpaceship *player_)
    {
        if(player_ != nullptr && !player_->IsPendingDestroy())
        {
            player_->SetShooter(std::move(unique<Shooter>{new ThreeWayShooter{player_, 0.4f, {50.f, 0.f}}}));
        }
    }

    void RewardFrontalWiper(PlayerSpaceship *player_)
    {
        if(player_ != nullptr && !player_->IsPendingDestroy())
        {
            player_->SetShooter(std::move(unique<Shooter>{new FrontalWiper{player_, 0.4f, {50.f, 0.f}}}));
        }
    }

    void RewardLife(PlayerSpaceship *player_)
    {
        if(!PlayerManager::Get().GetPlayer())
            return;

        PlayerManager::Get().GetPlayer()->AddLifeCount(1);
    }
} // namespace ly

