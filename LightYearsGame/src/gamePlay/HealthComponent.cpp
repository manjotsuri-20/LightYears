#include "gamePlay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
    HealthComponent::HealthComponent(float health_, float maxHealth_)
        : mHealth{health_},
        mMaxHealth{maxHealth_}
    {
    }

    float HealthComponent::GetHealth() const
    {
        return mHealth;
    }

    float HealthComponent::GetMaxHealth() const
    {
        return mMaxHealth;
    }

    void HealthComponent::TakenDamage(float amt_)
    {
        onTakenDamage.Broadcast(amt_, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmpty.Broadcast();
    }

    void HealthComponent::HealthRegen(float amt_)
    {
        LOG("Health regen: %f, now health is %f/%f", amt_, mHealth, mMaxHealth);
    }

    void HealthComponent::ChangeHealth(float amt_)
    {
        if(amt_ == 0) return;

        if(mHealth == 0) return;

        mHealth += amt_;

        if(mHealth < 0)
        {
            mHealth = 0;
        }

        if(mHealth > mMaxHealth)
        {
            mHealth = mMaxHealth;
        }

        if(amt_ < 0)
        {
            TakenDamage(amt_);
            if(mHealth <= 0)
            {
                HealthEmpty();
            }
        }
        onHealthChanged.Broadcast(amt_, mHealth, mMaxHealth);
    }
    

} // namespace ly
