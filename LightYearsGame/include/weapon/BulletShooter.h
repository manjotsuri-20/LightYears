#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"
#include "framework/Core.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
        public:
            BulletShooter(Actor* owner_, float coolDownTime_ = 1.f);
            virtual bool IsOnCoolDown() const;

        private:
            virtual void ShootImpl() override;
            sf::Clock mCooldownClock;
            float mCoolDownTime;
    };
} // namespace ly
