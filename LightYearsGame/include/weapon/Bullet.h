#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
        public:
            Bullet(World* world_, Actor* owner_, const std::string& texturePath_, float speed_ = 600.f, float damage_ = 10.f);

            void SetSpeed(float newSpeed_);
            void SetDamage(float newDamage_);

            float GetDamage() const { return mDamage; }

            virtual void Tick(float deltaTime_) override;
            virtual void BeginPlay() override;

        private:
            virtual void OnActorBeginOverlap(Actor* other_) override;
            void Move(float deltaTime_);
            Actor* mOwner;
            float mSpeed;
            float mDamage;
    };
} // namespace ly
