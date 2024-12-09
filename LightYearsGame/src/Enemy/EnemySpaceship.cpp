#include "Enemy/EnemySpaceship.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld_, const std::string& texturePath_, float collisionDamage_)
        : Spaceship{owningWorld_, texturePath_},
        mCollisionDamage{collisionDamage_}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltatTime_)
    {
        Spaceship::Tick(deltatTime_);
        if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
        {
            Destroy();
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other_)
    {
        Spaceship::OnActorBeginOverlap(other_);
        if(IsOtherHostile(other_))
        {
            other_->ApplyDamage(mCollisionDamage);
        }
    }
} // namespace ly

