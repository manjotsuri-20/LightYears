#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath_)
        : mOwningWorld(owningWorld), 
        mHasBeganPlay(false),
        mSprite{},
        mTexture{}
    {
        SetTexture(texturePath_);
    }

    void Actor::BeginPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime_)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime_);
        }
    }

    void Actor::BeginPlay()
    {
        // LOG("Actor began Play");
    }

    void Actor::Tick(float deltaTime_)
    {
        // LOG("Actor ticking");
    }

    void Actor::SetTexture(const std::string& texturePath_)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath_);
        if(!mTexture) return;
        mSprite.setTexture(*mTexture);

        int _textureWidth = mTexture->getSize().x;
        int _textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{_textureWidth, _textureHeight}});
        CentrePivot();
    }

    void Actor::Render(sf::RenderWindow& window_)
    {
        if(IsPendingDestroy())
        {
            return;
        }
        window_.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLoc_)
    {
        mSprite.setPosition(newLoc_);
    }

    void Actor::SetActorRotation(float newRot_)
    {
        mSprite.setRotation(newRot_);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmt_)
    {
        SetActorLocation(GetActorLocation() + offsetAmt_);
    }

    void Actor::AddActorRotationOffset(float offsetAmt_)
    {
        SetActorRotation(GetActorRotation() + offsetAmt_);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation() + 90.f);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    void Actor::CentrePivot()
    {
        sf::FloatRect _bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(_bound.width/2.f, _bound.height/2.f);
    }

    World* Actor::GetWorld() const
    {
        return mOwningWorld;
    }

    bool Actor::IsActorOutOfWindowBounds() const
    {
        float _windowWidth = GetWorld()->GetWindowSize().x;
        float _windowHeight = GetWorld()->GetWindowSize().y;

        float _width = GetActorGlobalBounds().width;
        float _height = GetActorGlobalBounds().height;

        sf::Vector2f _actorPosition = GetActorLocation();

        if(_actorPosition.x < -_width)
        {
            return true;
        }
        if(_actorPosition.x > _windowWidth + _width)
        {
            return true;
        }

        if(_actorPosition.y < -_height)
        {
            return true;
        }
        if(_actorPosition.y > _windowHeight + _height)
        {
            return true;
        }
        return false;
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }

}

