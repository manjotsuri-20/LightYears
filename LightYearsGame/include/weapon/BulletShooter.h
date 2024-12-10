#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"
#include "framework/Core.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
        public:
            BulletShooter(Actor* owner_, float coolDownTime_ = 1.f, sf::Vector2f localPositionOffset_ = {0.f, 0.f}, float localRotationOffset_ = 0, const std::string& bulletTexturePath_ = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
            virtual bool IsOnCoolDown() const;
            void SetBulletTexturePath(const std::string& bulletTexturePath);

        private:
            virtual void ShootImpl() override;
            sf::Clock mCooldownClock;
            float mCoolDownTime;
            sf::Vector2f mLocalPositionOffset;
            float mLocalRotationOffset;
            std::string mBulletTexturePath;
    };
} // namespace ly
