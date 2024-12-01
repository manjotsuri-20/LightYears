#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* owner_, float coolDownTime)
        : Shooter(owner_),
        mCooldownClock{},
        mCoolDownTime{coolDownTime}
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
        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() - 90.f);
        LOG("Shooting!");
    }
} // namespace ly
