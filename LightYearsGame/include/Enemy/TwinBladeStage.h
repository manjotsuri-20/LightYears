#pragma once
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class TwinBladeStage : public GameStage
    {
        public:
            TwinBladeStage(World* world_);
            virtual void StartStage() override;

        private:
            void SpawnTwinBlade();
            virtual void StageFinished() override;

            float mSpawnInterval;
            float mSpawnDistanceToCentre;

            sf::Vector2f mLeftSpawnLoc;
            sf::Vector2f mRightSpawnLoc;
            sf::Vector2f mSpawnLoc;

            int mSpawnAmt;
            int mCurrentSpawnCount;

            TimerHandle mSpawnTimerHandle;
    };
} // namespace ly
