#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly
{
    class FrontalWiper : public Shooter
    {
        public:
            FrontalWiper(Actor* owner_, float coolDownTime_ = 0.3f, const sf::Vector2f& localOffset_ = {0.f, 0.f}, float width_ = 60.f);

        private:
            virtual void ShootImpl() override;

            float mWidth;
            BulletShooter mShooter1;
            BulletShooter mShooter2;
            BulletShooter mShooter3;
            BulletShooter mShooter4;
    };
} // namespace ly
