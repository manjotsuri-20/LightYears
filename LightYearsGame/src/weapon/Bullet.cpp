#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(World *world_, Actor *owner_, const std::string &texturePath_, float speed_, float damage_)
        : Actor{world_, texturePath_},
        mOwner{owner_},
        mSpeed{speed_},
        mDamage{damage_}
    {
    }

    void Bullet::SetSpeed(float newSpeed_)
    {
        mSpeed = newSpeed_;
    }

    void Bullet::SetDamage(float newDamage_)
    {
        mDamage = newDamage_;
    }

    void Bullet::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);
        Move(deltaTime_);
        if(IsActorOutOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::Move(float deltaTime_)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime_);
    }

} //namespace ly
