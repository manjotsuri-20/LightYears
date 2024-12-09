#include "VFX/Explosion.h"
#include "framework/MathUtility.h"
#include "VFX/Particle.h"
#include "framework/World.h"

namespace ly
{
    Explosion::Explosion(int particleAmt_,
            float lifeTimeMin_,
            float lifeTimeMax_,
            float sizeMin_,
            float sizeMax_,
            float speedMin_,
            float speedMax_,
            const sf::Color& spawnParticleColor_,
            const List<std::string> particleImagePaths_)
        : mParticleAmt(particleAmt_),
        mLeftTimeMin{lifeTimeMin_},
        mLeftTimeMax{lifeTimeMax_},
        mSizeMin{sizeMin_},
        mSizeMax{sizeMax_},
        mSpeedMin{speedMin_},
        mSpeedMax{speedMax_},
        mParticleColor{spawnParticleColor_},
        mParticleImagePaths{particleImagePaths_}
    {
    }

    void Explosion::SpawnExplosion(World *world_, const sf::Vector2f& location_)
    {
        if(!world_) return;
        for(int i = 0; i < mParticleAmt; i++)
        {
            std::string particleImagePath_ = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
            weak<Particle> newParticle_ = world_->SpawnActor<Particle>(particleImagePath_);

            newParticle_.lock()->RandomLeftTime(mLeftTimeMin, mLeftTimeMax);
            newParticle_.lock()->SetActorLocation(location_);
            newParticle_.lock()->RandomSize(mSizeMin, mSizeMax);
            newParticle_.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
            newParticle_.lock()->GetSprite().setColor(mParticleColor);
        }
    }
} // namespace ly

