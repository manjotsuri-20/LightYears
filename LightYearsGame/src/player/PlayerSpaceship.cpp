#include "player/PlayerSpaceship.h"

#include "framework/MathUtility.h"
#include "framework/TimerManager.h"
#include "player/Player.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld_, const std::string& path_)
        : Spaceship{owningWorld_, path_}
        , mMoveInput{}
        , mSpeed(200.f)
        , mShooter{new BulletShooter{this, 0.15f, {50.f, 0.f}}}
        , mInvulnerableTime{2.f}
        , mInvulnerable{true}
        , mInvulnerableFlashInterval{0.5f}
        , mInvulnerableFlashTimer{0.f}
        , mInvulnerableFlashDirection{1}
    {
        SetTeamID(1);
    }

    void PlayerSpaceship::Tick(float deltaTime_)
    {
        Spaceship::Tick(deltaTime_);
        HandleInput();
        ConsumeInput(deltaTime_);
        UpdateInvulnerable(deltaTime_);
    }

    void PlayerSpaceship::BeginPlay()
    {
        Spaceship::BeginPlay();
        TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, mInvulnerableTime);
    }

    void PlayerSpaceship::StopInvulnerable()
    {
        GetSprite().setColor(sf::Color{255, 255, 255, 255});
        mInvulnerable = false;
    }

    void PlayerSpaceship::UpdateInvulnerable(float deltaTime_)
    {
        if (!mInvulnerable) return;

        mInvulnerableFlashTimer += deltaTime_ * mInvulnerableFlashDirection;
        if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
        {
            mInvulnerableFlashDirection *= -1;
        }

        GetSprite().setColor(LerpColor(sf::Color{255, 255, 255, 64}, sf::Color{255, 255, 255, 128}, mInvulnerableFlashTimer / mInvulnerableFlashInterval));
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
        if (_actorLocation.x < 0 && mMoveInput.x < 0)
        {
            mMoveInput.x = 0.f;
        }
        if (_actorLocation.x > GetWindowSize().x && mMoveInput.x > 0)
        {
            mMoveInput.x = 0.f;
        }
        if (_actorLocation.y < 0 && mMoveInput.y < 0)
        {
            mMoveInput.y = 0.f;
        }
        if (_actorLocation.y > GetWindowSize().y && mMoveInput.y > 0)
        {
            mMoveInput.y = 0.f;
        }
    }

    void PlayerSpaceship::Shoot()
    {
        if (mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::ApplyDamage(float amt_)
    {
        if (!mInvulnerable)
        {
            Spaceship::ApplyDamage(amt_);
        }
    }

    void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter_)
    {
        if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter_.get()))
        {
            mShooter->IncrementLevel();
            return;
        }
        mShooter = std::move(newShooter_);
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mMoveInput.y = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mMoveInput.x = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mMoveInput.x = 1.f;
        }

        ClampInputOnEdge();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
}  // namespace ly
