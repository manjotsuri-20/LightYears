#include "Enemy/Boss.h"

#include "Enemy/EnemySpaceship.h"
#include "gamePlay/HealthComponent.h"

namespace ly
{
    Boss::Boss(World* world_)
        : EnemySpaceship(world_, "SpaceShooterRedux/PNG/Enemies/boss.png")
        , mSpeed{100.f}
        , mBaseSpeed{100.f}
        , mSwitchDistanceToEdge{100.f}
        , mBaseShooterLeft{this, 1.0f, {50.f, -50.f}}
        , mBaseShooterRight{this, 1.0f, {50.f, 50.f}}
        , mThreeWayShooter{this, 4.f, {100.f, 0.f}}
        , mFrontalWiperLeft{this, 5.f, {80.f, -100.f}}
        , mFrontalWiperRight{this, 5.f, {80.f, 100.f}}
        , mStage{1}
        , mFinalStageShooterLeft{this, 0.3f, {50.f, -150.f}}
        , mFinalStageShooterRight{this, 0.3f, {50.f, 150.f}}
    {
        SetActorRotation(90.f);
        SetVelocity({mSpeed, 0.f});
        SetRewardSpawnWeight(0.f);
    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();

        HealthComponent& _healthComp = GetHealthComp();
        _healthComp.SetInitialHealth(3000.f, 3000.f);
        _healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
    }

    void Boss::Tick(float deltaTime_)
    {
        EnemySpaceship::Tick(deltaTime_);
        ShootBaseShooters();
        ShootThreeWayShooter();
        ShootFrontalWiper();
        if (mStage == 4)
        {
            mFinalStageShooterLeft.Shoot();
            mFinalStageShooterRight.Shoot();
        }
        CheckMove();
    }

    void Boss::CheckMove()
    {
        if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
        {
            SetVelocity({-mSpeed, 0.f});
        }
        else if (GetActorLocation().x < mSwitchDistanceToEdge)
        {
            SetVelocity({mSpeed, 0.f});
        }
    }

    void Boss::ShootBaseShooters()
    {
        mBaseShooterLeft.Shoot();
        mBaseShooterRight.Shoot();
    }

    void Boss::ShootThreeWayShooter()
    {
        mThreeWayShooter.Shoot();
    }

    void Boss::ShootFrontalWiper()
    {
        mFrontalWiperLeft.Shoot();
        mFrontalWiperRight.Shoot();
    }

    void Boss::HealthChanged(float amt_, float currentHealth_, float maxHealth_)
    {
        float _percentLeft = currentHealth_ / maxHealth_;
        if (_percentLeft < 0.7f && _percentLeft > 0.5f)
        {
            SetStage(2);
        }

        if (_percentLeft < 0.5f && _percentLeft > 0.3f)
        {
            SetStage(3);
        }

        if (_percentLeft < 0.3f)
        {
            SetStage(4);
        }
    }

    void Boss::SetStage(int newStage_)
    {
        mStage = newStage_;
        mBaseShooterLeft.SetCurrentLevel(mStage);
        mBaseShooterRight.SetCurrentLevel(mStage);
        mFrontalWiperLeft.SetCurrentLevel(mStage);
        mFrontalWiperRight.SetCurrentLevel(mStage);
        mThreeWayShooter.SetCurrentLevel(mStage);
        mSpeed = mStage * mBaseSpeed;
    }

}  // namespace ly
