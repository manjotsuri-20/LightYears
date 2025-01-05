#pragma once
#include "SFML/System/Vector2.hpp"
#include "framework/Actor.h"

namespace ly
{
    class BackdropActor : public Actor
    {
        public:
            BackdropActor(World* owningWorld_, const std::string& texture_, const sf::Vector2f& velocity_ = sf::Vector2f{0.f, -50.f});
            virtual void Tick(float deltaTime_) override;

        private:
            sf::Vector2f mMovingVelocity;
            float mLeftShift;
            float mTopShift;
    };
}  // namespace ly
