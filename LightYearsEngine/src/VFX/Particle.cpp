#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
    Particle::Particle(World* owningWorld_, const std::string& texturePath_)
        : Actor{owningWorld_, texturePath_},
        mVelocity{},
        mLifeTime{1.f},
        mTimer{}
    {
    }

    void Particle::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);

        Move(deltaTime_);
        Fade(deltaTime_);

        if(mTimer.getElapsedTime().asSeconds() >= mLifeTime)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float minSpeed_, float maxSpeed_)
    {
        mVelocity = RandomUnitVector() * RandomRange(minSpeed_, maxSpeed_);
    }

    void Particle::RandomSize(float min_, float max_)
    {
        float randScale_ = RandomRange(min_, max_);
        GetSprite().setScale(randScale_, randScale_);
    }

    void Particle::RandomLeftTime(float min_, float max_)
    {
        mLifeTime = RandomRange(min_, max_);
    }

    void Particle::Move(float deltaTime_)
    {
        AddActorLocationOffset(mVelocity * deltaTime_);
    }

    void Particle::Fade(float deltaTime_)
    {
        float _elapsedTime = mTimer.getElapsedTime().asSeconds();
        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), _elapsedTime/mLifeTime));
        GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{0, 0}, _elapsedTime/mLifeTime));
    }
} // namespace ly
