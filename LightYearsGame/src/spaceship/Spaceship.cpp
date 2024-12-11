#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
    Spaceship::Spaceship(World *owningWorld_, const std::string &texturePath_)
        :Actor(owningWorld_, texturePath_),
        mVelocity{},
        mHeathComponent{100.f, 100.f},
        mBlinkTime{0.f},
        mBlinkDuration{0.2f},
        mBlinkColorOffset{255, 0, 0, 255}
    {
    }

    void Spaceship::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);
        AddActorLocationOffset(GetVelocity() * deltaTime_);
        UpdateBlink(deltaTime_);
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

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);

        mHeathComponent.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHeatlhChanged);
        mHeathComponent.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHeathComponent.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amt_)
    {
        mHeathComponent.ChangeHealth(-amt_);
    }

    void Spaceship::OnHeatlhChanged(float amt_, float health_, float maxHealth_)
    {
    }

    void Spaceship::OnTakenDamage(float amt_, float health_, float maxHealth_)
    {
        Blink();
    }

    void Spaceship::Blow()
    {
        Explosion* exp_  = new Explosion();
        exp_->SpawnExplosion(GetWorld(), GetActorLocation());
        Blew();
        Destroy();
        delete exp_;
    }

    void Spaceship::Blink()
    {
        if(mBlinkTime == 0)
        {
            mBlinkTime = mBlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime_)
    {
        if(mBlinkTime > 0)
        {
            mBlinkTime -= deltaTime_;
            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
        }
    }

    void Spaceship::Blew()
    {
        
    }
} // namespace ly

