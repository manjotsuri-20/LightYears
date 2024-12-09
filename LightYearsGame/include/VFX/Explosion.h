#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class World;
    class Explosion
    {
        public: 
            Explosion(int particleAmt_ = 20, 
            float lifeTimeMin_ = 0.5f,
            float lifeTimeMax_ = 1.5f,
            float sizeMax_ = 1,
            float sizeMin_ = 3,
            float speedMin_ = 200,
            float speedMax_ = 400,
            const sf::Color& spawnParticleColor_ = sf::Color{255, 128, 0, 255},
            const List<std::string> particleImagePaths_ = 
            {
                "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"
            }
            );

            void SpawnExplosion(World* world_, const sf::Vector2f& location_);

        private:
            int mParticleAmt;
            List<std::string> mParticleImagePaths;
            float mLeftTimeMin;
            float mLeftTimeMax;
            float mSizeMin;
            float mSizeMax;
            float mSpeedMin;
            float mSpeedMax;
            sf::Color mParticleColor;
    };
} // namespace ly
