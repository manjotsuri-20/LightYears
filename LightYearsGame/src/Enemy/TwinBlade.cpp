#include "Enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    TwinBlade::TwinBlade(World* owningWorld_, const std::string& texturePath_, const sf::Vector2f& velocity_)
        : EnemySpaceship{owningWorld_, texturePath_},
        mShooterLeft{new BulletShooter{this, 1.f, {50.f, -20.f}}},
        mShooterRight{new BulletShooter{this, 1.f, {50.f, 20.f}}}
    {
        SetVelocity(velocity_);
        SetActorRotation(90.0f);
    }

    void TwinBlade::Tick(float deltaTime_)
    {
        EnemySpaceship::Tick(deltaTime_);
        Shoot();
    }

    void TwinBlade::Shoot()
    {
        mShooterLeft->Shoot();
        mShooterRight->Shoot();
    }

} // namespace ly
