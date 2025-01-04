#include "weapon/ThreeWayShooter.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(Actor* owner_, float coolDownTime_, const sf::Vector2f& localOffset_)
        : Shooter{owner_}
        , mShooterLeft{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, -10.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
        , mShooterMid{owner_, coolDownTime_, localOffset_, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
        , mShooterRight{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, 10.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
        , mTopLevelShooterLeft{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, 10.f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
        , mTopLevelShooterRight{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, -10.f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {
    }

    void ThreeWayShooter::ShootImpl()
    {
        mShooterLeft.Shoot();
        mShooterMid.Shoot();
        mShooterRight.Shoot();

        if (GetCurrentLevel() == GetMaxlevel())
        {
            mTopLevelShooterLeft.Shoot();
            mTopLevelShooterRight.Shoot();
        }
    }

    void ThreeWayShooter::IncrementLevel(int amt_)
    {
        Shooter::IncrementLevel(amt_);
        mShooterLeft.IncrementLevel(amt_);
        mShooterMid.IncrementLevel(amt_);
        mShooterRight.IncrementLevel(amt_);
        mTopLevelShooterLeft.IncrementLevel(amt_);
        mTopLevelShooterRight.IncrementLevel(amt_);
    }

    void ThreeWayShooter::SetCurrentLevel(int newLevel_)
    {
        Shooter::SetCurrentLevel(newLevel_);
        mShooterLeft.SetCurrentLevel(newLevel_);
        mShooterMid.SetCurrentLevel(newLevel_);
        mShooterRight.SetCurrentLevel(newLevel_);
        mTopLevelShooterLeft.SetCurrentLevel(newLevel_);
        mTopLevelShooterRight.SetCurrentLevel(newLevel_);
    }
}  // namespace ly
