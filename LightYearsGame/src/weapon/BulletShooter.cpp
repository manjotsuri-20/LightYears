#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner_, float coolDownTime, sf::Vector2f localPositionOffset_, float localRotationOffset_, const std::string& bulletTexturePath_)
        : Shooter(owner_),
        mCooldownClock{},
        mCoolDownTime{coolDownTime},
        mLocalPositionOffset{localPositionOffset_},
        mLocalRotationOffset{localRotationOffset_},
        mBulletTexturePath{bulletTexturePath_}
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

    void BulletShooter::SetBulletTexturePath(const std::string &bulletTexturePath)
    {
        mBulletTexturePath = bulletTexturePath;
    }

    void BulletShooter::ShootImpl()
    {
        sf::Vector2f _ownerForwardDirection  = GetOwner()->GetActorForwardDirection();
        sf::Vector2f _ownerRightDirection = GetOwner()->GetActorRightDirection();

        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + _ownerForwardDirection * mLocalPositionOffset.x + _ownerRightDirection * mLocalPositionOffset.y);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
        // LOG("Shooting!");
    }
} // namespace ly
