#pragma once
#include "framework/Actor.h"
#include <functional>

namespace ly
{
    class PlayerSpaceship;
    class Reward;
    using RewardFunc = std::function<void(PlayerSpaceship*)>;
    using RewardFactoryFunc = std::function<weak<Reward>(World*)>;
    class Reward : public Actor
    {
        public: 
            Reward(World* world_, const std::string& texturePath_, RewardFunc rewardFunction_, float speed_ = 200.f);
            virtual void BeginPlay() override;
            virtual void Tick(float deltaTime_) override;

        private:
            virtual void OnActorBeginOverlap(Actor* otherActor_);
            float mSpeed;
            RewardFunc mRewardFunc;
    };

    weak<Reward> CreateHealthReward(World* world_);
    weak<Reward> CreateThreeWayShooterReward(World* world_);
    weak<Reward> CreateFrontalWiperReward(World* world_);
    weak<Reward> CreateLifeReward(World* world_);

    weak<Reward> CreateReward(World* world_, const std::string& texturePath_, RewardFunc rewardFunc_);

    void RewardHealth(PlayerSpaceship* player_);
    void RewardThreeWayShooter(PlayerSpaceship* player_);
    void RewardFrontalWiper(PlayerSpaceship* player_);
    void RewardLife(PlayerSpaceship* player_);
} // namespace ly
