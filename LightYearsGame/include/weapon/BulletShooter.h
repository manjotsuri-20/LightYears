#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"
#include "framework/Core.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
        public:
            BulletShooter(Actor* owner_, float coolDownTime_ = 1.f, sf::Vector2f localPositionOffset_ = {0.f, 0.f}, float localRotationOffset_ = 0);
            virtual bool IsOnCoolDown() const;

        private:
            virtual void ShootImpl() override;
            sf::Clock mCooldownClock;
            float mCoolDownTime;
            sf::Vector2f mLocalPositionOffset;
            float mLocalRotationOffset;
    };
} // namespace ly
