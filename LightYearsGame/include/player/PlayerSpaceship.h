#pragma once
#include "spaceship/Spaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
        public:
            PlayerSpaceship(World* owningWorld_, const std::string& path_ = "SpaceShooterRedux/PNG/playerShip1_blue.png");
            virtual void Tick(float deltaTime_) override;
            void SetSpeed(float newSpeed_);
            float GetSpeed() const;
            void ClampInputOnEdge();
            virtual void Shoot() override;

        private:
            void HandleInput();
            void NormalizeInput();
            void ConsumeInput(float deltaTime_);
            
            sf::Vector2f mMoveInput;
            float mSpeed;

            unique<BulletShooter> mShooter;
    };
} // namespace ly