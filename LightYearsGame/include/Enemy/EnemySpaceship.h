#pragma once
#include "spaceship/Spaceship.h"
#include "framework/Actor.h"
#include "player/Reward.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
        public:
            EnemySpaceship(World* owningWorld_, 
            const std::string& texturePath_, 
            float collisionDamage_ = 200.f, 
            float rewardSpawnWeight_ = 0.5f,
            const List<RewardFactoryFunc> rewards_ =
                {
                    CreateHealthReward,
                    CreateThreeWayShooterReward,
                    CreateFrontalWiperReward,
                    CreateLifeReward
                }
            );

            virtual void Tick(float deltatTime_) override;
            void SetScoreRewardAmt(unsigned int amt_);

        private:
            void SpawnReward();
            virtual void Blew() override;
            virtual void OnActorBeginOverlap(Actor* other_);
            float mCollisionDamage;
            unsigned int mScoreRewardAmt;
            float mRewardSpawnWeight;
            List<RewardFactoryFunc> mRewardFactories;
    };
} // namespace ly
