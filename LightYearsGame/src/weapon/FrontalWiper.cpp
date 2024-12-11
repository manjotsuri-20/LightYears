#include "weapon/FrontalWiper.h"

namespace ly
{
    FrontalWiper::FrontalWiper(Actor* owner_, float coolDownTime_, const sf::Vector2f& localOffset_, float width_)
        : Shooter(owner_),
        mWidth{width_},
        mShooter1{owner_, coolDownTime_, {localOffset_.x, localOffset_.y - width_/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter2{owner_, coolDownTime_, {localOffset_.x, localOffset_.y - width_/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter3{owner_, coolDownTime_, {localOffset_.x, localOffset_.y + width_/6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter4{owner_, coolDownTime_, {localOffset_.x, localOffset_.y + width_/2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter5{owner_, 0.1f, {localOffset_.x, localOffset_.y + width_/1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter6{owner_, 0.1f, {localOffset_.x, localOffset_.y - width_/1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {}

    void FrontalWiper::ShootImpl()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();

        if(GetCurrentLevel() == GetMaxlevel())
        {
            mShooter5.Shoot();
            mShooter6.Shoot();
        }
    }

    void FrontalWiper::IncrementLevel(int amt_)
    {
        Shooter::IncrementLevel(amt_);
        mShooter1.IncrementLevel(amt_);
        mShooter2.IncrementLevel(amt_);
        mShooter3.IncrementLevel(amt_);
        mShooter4.IncrementLevel(amt_);

        mShooter5.IncrementLevel(amt_);
        mShooter6.IncrementLevel(amt_);
    }
} // namespace ly
