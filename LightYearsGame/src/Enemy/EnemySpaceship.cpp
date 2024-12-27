#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld_, const std::string& texturePath_, float collisionDamage_, float rewardSpawnWeight_, const List<RewardFactoryFunc> rewards_)
        : Spaceship{owningWorld_, texturePath_},
        mCollisionDamage{collisionDamage_},
        mRewardSpawnWeight{rewardSpawnWeight_},
        mScoreRewardAmt{10},
        mRewardFactories{rewards_}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltatTime_)
    {
        Spaceship::Tick(deltatTime_);
        if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SetScoreRewardAmt(unsigned int amt_)
    {
        mScoreRewardAmt = amt_;
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other_)
    {
        Spaceship::OnActorBeginOverlap(other_);
        if(IsOtherHostile(other_))
        {
            other_->ApplyDamage(mCollisionDamage);
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
        Player* _player = PlayerManager::Get().GetPlayer();
        if(_player)
        {
            _player->AddScore(mScoreRewardAmt);
        }
    }

    void EnemySpaceship::SpawnReward()
    {
        if(mRewardFactories.size() == 0) return;

        if(mRewardSpawnWeight > RandomRange(0, 1))
            return;

        int _pick = (int)RandomRange(0, mRewardFactories.size());
        if(_pick >= 0 && _pick < mRewardFactories.size())
        {
            weak<Reward> _newReward = mRewardFactories[_pick](GetWorld());
            _newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }
} // namespace ly

