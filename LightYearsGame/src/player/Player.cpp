#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Player::Player()
        : mLifeCount{3},
        mScore{0},
        mCurrentPlayerSpaceship{}
    {}

    weak<PlayerSpaceship> Player::SpawnPlayerSpaceship(World *world_)
    {
        if(mLifeCount > 0)
        {
            --mLifeCount;
            auto _windowSize = world_->GetWindowSize();
            mCurrentPlayerSpaceship = world_->SpawnActor<PlayerSpaceship>();
            mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(_windowSize.x/2.f, _windowSize.y - 100.f));
            mCurrentPlayerSpaceship.lock()->SetActorRotation(-90.f);
            onLifeChange.Broadcast(mLifeCount);
            return mCurrentPlayerSpaceship;
        }
        else
        {
            mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
            onLifeExhausted.Broadcast();
        }
        return weak<PlayerSpaceship>{};
    }

    void Player::AddLifeCount(unsigned int count_)
    {
        if(count_ > 0)
        {
            mLifeCount += count_;
            onLifeChange.Broadcast(mLifeCount);
        }
    }

    void Player::AddScore(unsigned int amt_)
    {
        if(amt_ > 0)
        {
            mScore += amt_;
            onScoreChange.Broadcast(mScore);
        }
    }

} // namespace ly
