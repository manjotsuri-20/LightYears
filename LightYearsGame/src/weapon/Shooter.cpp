#include "weapon/Shooter.h"

namespace ly
{
    void Shooter::Shoot()
    {
        if(CanShoot() && !IsOnCoolDown())
        {
            ShootImpl();
        }
    }

    bool Shooter::CanShoot() const
    {
        return true;
    }

    bool Shooter::IsOnCoolDown() const
    {
        return false;
    }

    Actor *Shooter::GetOwner() const
    {
        return mOwner;
    }

    Shooter::Shooter(Actor *owner_)
        : mOwner(owner_),
        mCurrentLevel{1},
        mMaxLevel{4}
    {

    }

    void Shooter::IncrementLevel(int amt_)
    {
        if(mCurrentLevel == mMaxLevel) return;
        ++mCurrentLevel;
    }
} // namespace ly

