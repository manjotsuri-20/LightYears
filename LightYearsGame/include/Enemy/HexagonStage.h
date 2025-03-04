#pragma once
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"

namespace ly
{
    class HexagonStage : public GameStage
    {
        public:
            HexagonStage(World* world_);

            virtual void StartStage() override;

        private:
            virtual void StageFinished() override;
            void SpawnHexagon();

            float mSpawnInterval;
            float mSideSpawnOffset;
            int mSpawnGroupAmt;
            int mCurrentSpawnCount;

            sf::Vector2f mMidSpawnLoc;
            sf::Vector2f mLeftSpawnLoc;
            sf::Vector2f mRightSpawnLoc;

            TimerHandle mSpawnTimer;
    };
} // namespace ly
