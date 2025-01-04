#pragma once

#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"
namespace ly
{
    class Boss : public EnemySpaceship
    {
        public:
            Boss(World* world_);
            virtual void Tick(float deltaTime_) override;
            virtual void BeginPlay() override;

        private:
            float mSpeed;
            float mBaseSpeed;
            float mSwitchDistanceToEdge;
            void CheckMove();

            BulletShooter mBaseShooterLeft;
            BulletShooter mBaseShooterRight;
            ThreeWayShooter mThreeWayShooter;
            FrontalWiper mFrontalWiperLeft;
            FrontalWiper mFrontalWiperRight;

            BulletShooter mFinalStageShooterLeft;
            BulletShooter mFinalStageShooterRight;

            void ShootBaseShooters();
            void ShootThreeWayShooter();
            void ShootFrontalWiper();
            void HealthChanged(float amt_, float currentHealth_, float maxHealth_);

            int mStage;
            void SetStage(int newStage_);
    };
}  // namespace ly
