#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>
#include "framework/Actor.h"

namespace ly
{
    class PhysicsContactListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact* contact_) override;
        virtual void EndContact(b2Contact* contact_) override;
    };

    class PhysicsSystem
    {
        public:
            static PhysicsSystem& Get();
            void Step(float deltaTime_);
            b2Body* AddListener(Actor* listener_);
            void RemoveListener(b2Body* bodyToRemove_);
            float GetPhysicsScale() const;
            static void Cleanup();

        protected:
            PhysicsSystem();

        private:
            void ProcessPendingRemoveListeners();
            static unique<PhysicsSystem> mPhysicsSystem;
            b2World mPhysicsWorld;
            float mPhysicsScale;
            int mVelocityInterations;
            int mPositionInterations;
            PhysicsContactListener mContactListener;
            Set<b2Body*> mPendingRemovalListeners;
    };
} // namespace ly
