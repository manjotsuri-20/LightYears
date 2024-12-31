#pragma once
#include "framework/TimerManager.h"
#include "spaceship/Spaceship.h"
#include "weapon/Shooter.h"

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
            void SetShooter(unique<Shooter>&& newShooter_);
            virtual void ApplyDamage(float amt_) override;
            virtual void BeginPlay() override;

        private:
            void HandleInput();
            void NormalizeInput();
            void ConsumeInput(float deltaTime_);
            void StopInvulnerable();
            void UpdateInvulnerable(float deltaTime_);

            sf::Vector2f mMoveInput;
            float mSpeed;

            unique<Shooter> mShooter;

            float mInvulnerableTime;
            TimerHandle mInvulnerableTimerHandle;
            bool mInvulnerable;

            float mInvulnerableFlashInterval;
            float mInvulnerableFlashTimer;
            float mInvulnerableFlashDirection;
    };
}  // namespace ly
