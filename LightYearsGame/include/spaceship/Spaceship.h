#pragma once
#include "framework/Actor.h"

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

        private:
            sf::Vector2f mVelocity;
    };
} // namespace ly
