#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld_, const std::string &path_)
        :Spaceship{owningWorld_, path_},
        mMoveInput{},
        mSpeed(200.f),
        mShooter{new BulletShooter{this, 0.2f}}
    {
    }

    void PlayerSpaceship::Tick(float deltaTime_)
    {
        Spaceship::Tick(deltaTime_);
        HandleInput();
        ConsumeInput(deltaTime_);
    }

    void PlayerSpaceship::SetSpeed(float newSpeed_)
    {
        mSpeed = newSpeed_;
    }

    float PlayerSpaceship::GetSpeed() const
    {
        return mSpeed;
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f _actorLocation = GetActorLocation();
        if(_actorLocation.x < 0 && mMoveInput.x < 0)
        {
            mMoveInput.x = 0.f;
        }
        if(_actorLocation.x > GetWindowSize().x && mMoveInput.x > 0)
        {
            mMoveInput.x = 0.f;
        }
        if(_actorLocation.y < 0 && mMoveInput.y < 0)
        {
            mMoveInput.y = 0.f;
        }
        if(_actorLocation.y > GetWindowSize().y && mMoveInput.y > 0)
        {
            mMoveInput.y = 0.f;
        }
    }

    void PlayerSpaceship::Shoot()
    {
        if(mShooter)
        {
            mShooter->Shoot();
        }
    }
    
    void PlayerSpaceship::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mMoveInput.y = 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mMoveInput.x = -1.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mMoveInput.x = 1.f;
        }

        ClampInputOnEdge();
        NormalizeInput();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(mMoveInput);
        // LOG("Input Normalized %f %f", mMoveInput.x, mMoveInput.y);
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime_)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }
} // namespace ly

