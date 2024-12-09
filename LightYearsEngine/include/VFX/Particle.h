#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Particle : public Actor
    {
        public:
            Particle(World* owningWorld_, const std::string& texturePath_);
            virtual void Tick(float deltaTime_) override;

            void RandomVelocity(float minSpeed_, float maxSpeed_);
            void RandomSize(float min_, float max_);
            void RandomLeftTime(float min_, float max_);

        private:
            void Move(float deltaTime_);
            void Fade(float deltaTime_);
            sf::Vector2f mVelocity;
            float mLifeTime;
            sf::Clock mTimer;
    };
} // namespace ly
