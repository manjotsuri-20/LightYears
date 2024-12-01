#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Actor;
    class Shooter
    {
        public: 
            void Shoot();

            virtual bool CanShoot() const;
            virtual bool IsOnCoolDown() const;
            Actor* GetOwner() const;

        protected:
            Shooter(Actor* owner_);

        private:
            virtual void ShootImpl() = 0;
            Actor* mOwner;

    };
} // namespace ly
