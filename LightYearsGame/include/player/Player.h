#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"
#include "framework/Core.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    class World;
    class Player : public Object
    {
        public:
            Player();

            weak<PlayerSpaceship> SpawnPlayerSpaceship(World* world_);
            const weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; }

            void AddLifeCount(unsigned int count_);
            int GetLifeCount() const { return mLifeCount; }

            void AddScore(unsigned int amt_);
            int GetScore() const { return mScore; }

            Delegate<int> onLifeChange;
            Delegate<int> onScoreChange;
            Delegate<> onLifeExhausted;

        private:
            unsigned int mLifeCount;
            unsigned int mScore;
            weak<PlayerSpaceship> mCurrentPlayerSpaceship;
    };
} // namespace ly
