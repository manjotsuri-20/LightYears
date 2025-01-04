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

            int GetCurrentLevel() const
            {
                return mCurrentLevel;
            }

            int GetMaxlevel() const
            {
                return mMaxLevel;
            }

            virtual void SetCurrentLevel(int newLevel_);
            virtual void IncrementLevel(int amt_ = 1);

        protected:
            Shooter(Actor* owner_);

        private:
            virtual void ShootImpl() = 0;
            Actor* mOwner;

            int mCurrentLevel;
            int mMaxLevel;
    };
}  // namespace ly
