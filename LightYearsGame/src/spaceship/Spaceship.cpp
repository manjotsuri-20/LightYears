#include "spaceship/Spaceship.h"
#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(World *owningWorld_, const std::string &texturePath_)
        :Actor(owningWorld_, texturePath_),
        mVelocity{}
    {
    }

    void Spaceship::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);
        AddActorLocationOffset(GetVelocity() * deltaTime_);
    }

    void Spaceship::SetVelocity(const sf::Vector2f &newVel_)
    {
        mVelocity = newVel_;
    }
    
    sf::Vector2f Spaceship::GetVelocity() const
    {
        return mVelocity;
    }

    void Spaceship::Shoot()
    {

    }
} // namespace ly

