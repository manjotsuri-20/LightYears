#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld_, const std::string& texturePath_, float collisionDamage_, const List<RewardFactoryFunc> rewards_)
        : Spaceship{owningWorld_, texturePath_},
        mCollisionDamage{collisionDamage_},
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
    }

    void EnemySpaceship::SpawnReward()
    {
        if(mRewardFactories.size() == 0) return;

        int _pick = (int)RandomRange(0, mRewardFactories.size());
        if(_pick >= 0 && _pick < mRewardFactories.size())
        {
            weak<Reward> _newReward = mRewardFactories[_pick](GetWorld());
            _newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }


} // namespace ly

