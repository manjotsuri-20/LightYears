#pragma once
#include "spaceship/Spaceship.h"
#include "framework/Actor.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
        public:
            EnemySpaceship(World* owningWorld_, const std::string& texturePath_, float collisionDamage_ = 200.f);

            virtual void Tick(float deltatTime_) override;

        private:
            virtual void OnActorBeginOverlap(Actor* other_);
            float mCollisionDamage;
    };
} // namespace ly
