#include "weapon/ThreeWayShooter.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(Actor* owner_, float coolDownTime_, const sf::Vector2f& localOffset_)
        : Shooter{owner_},
        mShooterLeft{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, -10.f} , -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterMid{owner_, coolDownTime_, localOffset_ , 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterRight{owner_, coolDownTime_, localOffset_ + sf::Vector2f{10.f, 10.f} , 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {}

    void ThreeWayShooter::ShootImpl()
    {
        mShooterLeft.Shoot();
        mShooterMid.Shoot();
        mShooterRight.Shoot();

    }
} // namespace ly
