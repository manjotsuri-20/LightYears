#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath_)
        : mOwningWorld(owningWorld), 
        mHasBeganPlay(false),
        mSprite{},
        mTexture{},
        mPhysicsBody{nullptr},
        mPhysicsEnable{false},
        mTeamID{GetNeutralTeamID()}
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
        UpdatePhysicsTransform();
    }

    void Actor::SetActorRotation(float newRot_)
    {
        mSprite.setRotation(newRot_);
        UpdatePhysicsTransform();
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

    void Actor::InitializePhysics()
    {
        if(!mPhysicsBody)
        {
            mPhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }
            
    void Actor::UnInitializedPhysics()
    {
        if(mPhysicsBody)
        {
            PhysicsSystem::Get().RemoveListener(mPhysicsBody);
            mPhysicsBody = nullptr;
        }
    }

    const World* Actor::GetWorld() const
    {
        return mOwningWorld;
    }

    bool Actor::IsActorOutOfWindowBounds(float allowance_) const
    {
        float _windowWidth = GetWorld()->GetWindowSize().x;
        float _windowHeight = GetWorld()->GetWindowSize().y;

        float _width = GetActorGlobalBounds().width;
        float _height = GetActorGlobalBounds().height;

        sf::Vector2f _actorPosition = GetActorLocation();

        if(_actorPosition.x < -_width - allowance_)
        {
            return true;
        }
        if(_actorPosition.x > _windowWidth + _width + allowance_)
        {
            return true;
        }

        if(_actorPosition.y < -_height - allowance_)
        {
            return true;
        }
        if(_actorPosition.y > _windowHeight + _height + allowance_)
        {
            return true;
        }
        return false;
    }

    void Actor::SetEnablePhysics(bool enable_)
    {
        mPhysicsEnable = enable_;
        if(mPhysicsEnable)
        {
            InitializePhysics();
        }
        else
        {
            UnInitializedPhysics();
        }
    }

    void Actor::UpdatePhysicsTransform()
    {
        if(mPhysicsBody)
        {
            float _physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 _pos{GetActorLocation().x * _physicsScale, GetActorLocation().y * _physicsScale};
            float _rotation = DegreesToRadians(GetActorRotation());

            mPhysicsBody->SetTransform(_pos, _rotation);
        }
    }

    void Actor::OnActorBeginOverlap(Actor *other_)
    {
        // LOG("Overlapped");
    }

    void Actor::OnActorEndOverlap(Actor *other_)
    {
        // LOG("Overlapped finsish");
    }

    void Actor::Destroy()
    {
        UnInitializedPhysics();
        onActorDestroy.Broadcast(this);
        Object::Destroy();
    }

    bool Actor::IsOtherHostile(Actor* other_) const
    {
        if(other_ == nullptr) return false;

        if(GetTeamID() == GetNeutralTeamID() || other_->GetTeamID() == GetNeutralTeamID())
        {
            return false;
        }
   
        return GetTeamID() != other_->GetTeamID();
    }

    void Actor::ApplyDamage(float amt_)
    {
        
    }


    Actor::~Actor()
    {
        // LOG("Actor Destroyed");
    }

}

