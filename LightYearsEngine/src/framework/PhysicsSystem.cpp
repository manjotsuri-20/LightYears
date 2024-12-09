#include "framework/PhysicsSystem.h"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include "framework/MathUtility.h"
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem::mPhysicsSystem{nullptr};

    PhysicsSystem& PhysicsSystem::Get()
    {
        if(!mPhysicsSystem)
        {
            mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }
        return *mPhysicsSystem;
    }

    void PhysicsSystem::Step(float deltaTime_)
    {
        ProcessPendingRemoveListeners();
        mPhysicsWorld.Step(deltaTime_, mVelocityInterations, mPositionInterations);
    }

    b2Body* PhysicsSystem::AddListener(Actor *listener_)
    {
        if(listener_->IsPendingDestroy())
        {
            return nullptr;
        }

        b2BodyDef _bodyDef;
        _bodyDef.type = b2_dynamicBody;
        _bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener_);
        _bodyDef.position.Set(listener_->GetActorLocation().x * GetPhysicsScale(), listener_->GetActorLocation().y * GetPhysicsScale());
        _bodyDef.angle = DegreesToRadians(listener_->GetActorRotation());

        b2Body* _body = mPhysicsWorld.CreateBody(&_bodyDef);
        b2PolygonShape _shape;
        auto _bound = listener_->GetActorGlobalBounds();
        _shape.SetAsBox(_bound.width/2.f * GetPhysicsScale(), _bound.height/2.f * GetPhysicsScale());

        b2FixtureDef _fixtureDef;
        _fixtureDef.shape = &_shape;
        _fixtureDef.density = 1.0f;
        _fixtureDef.friction = 0.3f;
        _fixtureDef.isSensor = true;

        _body->CreateFixture(&_fixtureDef);

        return _body;
    }

    void PhysicsSystem::RemoveListener(b2Body *bodyToRemove_)
    {
        mPendingRemovalListeners.insert(bodyToRemove_);
    }

    float PhysicsSystem::GetPhysicsScale() const
    {
        return mPhysicsScale;
    }

    void PhysicsSystem::Cleanup()
    {
        mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{b2Vec2{0.f, 0.f}},
          mPhysicsScale{0.01f},
          mVelocityInterations{8},
          mPositionInterations{3},
          mContactListener{},
          mPendingRemovalListeners{}
    {
        mPhysicsWorld.SetContactListener(&mContactListener);
        mPhysicsWorld.SetAllowSleeping(false);
    }

    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        for(auto _listener : mPendingRemovalListeners)
        {
            mPhysicsWorld.DestroyBody(_listener);
        }
        mPendingRemovalListeners.clear();
    }

    void PhysicsContactListener::BeginContact(b2Contact *contact_)
    {
        Actor* _actorA = reinterpret_cast<Actor*>(contact_->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* _actorB = reinterpret_cast<Actor*>(contact_->GetFixtureB()->GetBody()->GetUserData().pointer);

        if(_actorA && !_actorA->IsPendingDestroy())
        {
            _actorA->OnActorBeginOverlap(_actorB);
        }

        if(_actorB && !_actorB->IsPendingDestroy())
        {
            _actorB->OnActorBeginOverlap(_actorA);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact* contact_)
    {
        Actor* _actorA = nullptr;
        Actor* _actorB = nullptr;

        if(contact_->GetFixtureA() && contact_->GetFixtureA()->GetBody())
        {
            _actorA = reinterpret_cast<Actor*>(contact_->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if(contact_->GetFixtureB() && contact_->GetFixtureB()->GetBody())
        {
            _actorB = reinterpret_cast<Actor*>(contact_->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if(_actorA && !_actorA->IsPendingDestroy())
        {
            _actorA->OnActorEndOverlap(_actorB);
        }

        if(_actorB && !_actorB->IsPendingDestroy())
        {
            _actorB->OnActorEndOverlap(_actorA);
        }
    }


} // namespace ly

