#pragma once
#include "Enemy/EnemySpaceship.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class UFO : public EnemySpaceship
    {
        public:
            UFO(World* owningWorld_, const sf::Vector2f& velocity_, const std::string& texturePath_ = "SpaceShooterRedux/PNG/ufoBlue.png", float rotationSpeed_ = 40.f);

            virtual void Tick(float deltaTime_) override;

        private:
            virtual void Shoot() override;

            unique<BulletShooter> mShooter1;
            unique<BulletShooter> mShooter2;
            unique<BulletShooter> mShooter3;

            float mRotationSpeed;
    };
} // namespace ly
