#include "Enemy/Hexagon.h"

namespace ly
{
    Hexagon::Hexagon(World* owningWorld_, const std::string& texturePath_, const sf::Vector2f& velocity_)
        : EnemySpaceship{owningWorld_, texturePath_},
        mShooter1{new BulletShooter{this, 1.f, sf::Vector2f{20.f, 50.f}, 30.f}},
        mShooter2{new BulletShooter{this, 1.f, sf::Vector2f{20.f, -50.f}, -30.f}},
        mShooter3{new BulletShooter{this, 1.f, sf::Vector2f{50.f, 0.f}}},
        mShooter4{new BulletShooter{this, 1.f, sf::Vector2f{-50.f, 0.f}, -180.f}},
        mShooter5{new BulletShooter{this, 1.f, sf::Vector2f{-20.f, 50.f}, 120.f}},
        mShooter6{new BulletShooter{this, 1.f, sf::Vector2f{-20.f, -50.f}, -120.f}}
    {
        SetVelocity(velocity_);
        SetActorRotation(90.f);
    }

    void Hexagon::Tick(float deltaTime_)
    {
        EnemySpaceship::Tick(deltaTime_);
        Shoot();
    }

    void Hexagon::Shoot()
    {
        mShooter1->Shoot();
        mShooter2->Shoot();
        mShooter3->Shoot();
        mShooter4->Shoot();
        mShooter5->Shoot();
        mShooter6->Shoot();
    }

} // namespace ly
