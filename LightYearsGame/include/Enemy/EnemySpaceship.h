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
            const List<RewardFactoryFunc> rewards_ =
                {
                    CreateHealthReward,
                    CreateThreeWayShooterReward,
                    CreateFrontalWiperReward
                }
            );

            virtual void Tick(float deltatTime_) override;

        private:
            void SpawnReward();
            virtual void Blew() override;
            virtual void OnActorBeginOverlap(Actor* other_);
            float mCollisionDamage;
            List<RewardFactoryFunc> mRewardFactories;
    };
} // namespace ly
