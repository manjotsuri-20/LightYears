#include "Enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Vanguard::Vanguard(World* owningWorld_, const std::string& texturePath_, const sf::Vector2f& velocity_)
        : EnemySpaceship{owningWorld_, texturePath_},
        mShooter{new BulletShooter{this}}
    {
        SetVelocity(velocity_);
        SetActorRotation(180.0f);
    }

    void Vanguard::Tick(float deltaTime_)
    {
        EnemySpaceship::Tick(deltaTime_);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    }
} // namespace ly

