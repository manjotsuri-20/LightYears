#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class TwinBlade : public EnemySpaceship
    {
        public:
            TwinBlade(World* owningWorld_, const std::string& texturePath_ = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity_ = {0.f, 120.f});
            virtual void Tick(float deltaTime_) override;
            virtual void Shoot() override;

        private:
            unique<BulletShooter> mShooterLeft;
            unique<BulletShooter> mShooterRight;
    };
} // namespace ly
