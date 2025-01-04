#pragma once
#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
        public:
            HealthComponent(float health_, float maxHealth_);
            void ChangeHealth(float amt_);
            float GetHealth() const;
            float GetMaxHealth() const;

            Delegate<float, float, float> onHealthChanged;
            Delegate<float, float, float> onTakenDamage;
            Delegate<> onHealthEmpty;
            void SetInitialHealth(float health_, float maxHealth_);

        private:
            void TakenDamage(float amt_);
            void HealthEmpty();
            void HealthRegen(float amt_);
            float mHealth;
            float mMaxHealth;
    };
}  // namespace ly
