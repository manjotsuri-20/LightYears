#pragma once
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"

namespace ly
{
    class UFOStage : public GameStage
    {
        public:
            UFOStage(World* owningWorld_);
            virtual void StartStage() override;

        private:
            virtual void StageFinished() override;
            sf::Vector2f GetRandomSpawnLoc() const;
            void SpawnUFO();

            float mSpawnInterval;
            int mSpawnAmt;
            int mCurrentSpawnAmt;
            float mUFOSpeed;

            TimerHandle mSpawnTimer;
    };
} // namespace ly
