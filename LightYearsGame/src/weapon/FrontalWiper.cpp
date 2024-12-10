#include "weapon/FrontalWiper.h"

namespace ly
{
    FrontalWiper::FrontalWiper(Actor* owner_, float coolDownTime_, const sf::Vector2f& localOffset_, float width_)
        : Shooter(owner_),
        mWidth{width_},
        mShooter1{owner_, coolDownTime_, {localOffset_.x, localOffset_.y - width_/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter2{owner_, coolDownTime_, {localOffset_.x, localOffset_.y - width_/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter3{owner_, coolDownTime_, {localOffset_.x, localOffset_.y + width_/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter4{owner_, coolDownTime_, {localOffset_.x, localOffset_.y + width_/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {}

    void FrontalWiper::ShootImpl()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();
    }
} // namespace ly
