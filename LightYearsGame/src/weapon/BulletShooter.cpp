#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner_, float coolDownTime, sf::Vector2f localPositionOffset_, float localRotationOffset_)
        : Shooter(owner_),
        mCooldownClock{},
        mCoolDownTime{coolDownTime},
        mLocalPositionOffset{localPositionOffset_},
        mLocalRotationOffset{localRotationOffset_}
    {
    }

    bool BulletShooter::IsOnCoolDown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > mCoolDownTime)
        {
            return false;
        }
        return true;
    }
    
    void BulletShooter::ShootImpl()
    {
        sf::Vector2f _ownerForwardDirection  = GetOwner()->GetActorForwardDirection();
        sf::Vector2f _ownerRightDirection = GetOwner()->GetActorRightDirection();

        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + _ownerForwardDirection * mLocalPositionOffset.x + _ownerRightDirection * mLocalPositionOffset.y);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
        // LOG("Shooting!");
    }
} // namespace ly
