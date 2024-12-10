#pragma once
#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class Hexagon : public EnemySpaceship
    {
        public:
            Hexagon(World* owningWorld_, const std::string& texturePath_ = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity_ = sf::Vector2f{0.f, 100.f});

            virtual void Tick(float deltaTime_) override;
        
        private:
            virtual void Shoot() override;
            
            unique<BulletShooter> mShooter1;
            unique<BulletShooter> mShooter2;
            unique<BulletShooter> mShooter3;
            unique<BulletShooter> mShooter4;
            unique<BulletShooter> mShooter5;
            unique<BulletShooter> mShooter6;
    };
} // namespace ly
