#include "Enemy/UFO.h"

namespace ly
{
    UFO::UFO(World *owningWorld_, const sf::Vector2f& velocity_, const std::string& texturePath_, float rotationSpeed_)
        : EnemySpaceship{owningWorld_, texturePath_},
        mShooter1{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, -60.f}},
        mShooter2{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, 60.f}},
        mShooter3{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, 180.f}},
        mRotationSpeed{rotationSpeed_}
    {
        SetVelocity(velocity_);
        SetActorRotation(90.f);
    }

    void UFO::Tick(float deltaTime_)
    {
        EnemySpaceship::Tick(deltaTime_);
        Shoot();
        AddActorRotationOffset(mRotationSpeed * deltaTime_);
    }

    void UFO::Shoot()
    {
        mShooter1->Shoot();
        mShooter2->Shoot();
        mShooter3->Shoot();
    }

} // namespace ly

