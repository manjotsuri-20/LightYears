#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Vanguard : public EnemySpaceship
    {
        public:
            Vanguard(World* owningWorld_, const std::string& texturePath_ = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& velocity_ = {0.f, 50.f});

            virtual void Tick(float deltaTime_) override;

        private:
            virtual void Shoot() override;
            unique<BulletShooter> mShooter;
    };
} // namespace ly
