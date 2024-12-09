#pragma once
#include "framework/Actor.h"
#include "gamePlay/HealthComponent.h"

namespace ly
{
    class Spaceship : public Actor
    {
        public:
            Spaceship(World* owningWorld_, const std::string& texturePath_ = "");
            virtual void Tick(float deltaTime_) override;
            void SetVelocity(const sf::Vector2f& newVel_);
            sf::Vector2f GetVelocity() const;
            virtual void Shoot();
            virtual void BeginPlay() override;

            virtual void ApplyDamage(float amt_) override;

        private:
            void Blink();
            void UpdateBlink(float deltaTime_);
            virtual void OnHeatlhChanged(float amt_, float health_, float maxHealth_);
            virtual void OnTakenDamage(float amt_, float health_, float maxHealth_);
            virtual void Blow();
            sf::Vector2f mVelocity;
            HealthComponent mHeathComponent;
            
            float mBlinkTime;
            float mBlinkDuration;
            sf::Color mBlinkColorOffset;

    };
} // namespace ly
