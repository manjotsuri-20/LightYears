#pragma once
#include <SFML/Graphics.hpp>

#include "weapon/BulletShooter.h"

namespace ly
{
    class ThreeWayShooter : public Shooter
    {
        public:
            ThreeWayShooter(Actor* owner_, float coolDownTime_ = 0.3f, const sf::Vector2f& localOffset_ = {0.f, 0.f});

            BulletShooter mShooterLeft;
            BulletShooter mShooterMid;
            BulletShooter mShooterRight;

            BulletShooter mTopLevelShooterLeft;
            BulletShooter mTopLevelShooterRight;

            virtual void IncrementLevel(int amt_) override;
            virtual void SetCurrentLevel(int newLevel_) override;

        private:
            virtual void ShootImpl() override;
    };
}  // namespace ly
