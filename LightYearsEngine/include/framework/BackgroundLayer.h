#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "framework/Actor.h"

namespace ly
{
    class BackgroundLayer : public Actor
    {
        public:
            BackgroundLayer(World* owningWorld_, const List<std::string>& assetpaths_ = {}, const sf::Vector2f& minVel_ = sf::Vector2f{0.f, 50.f}, const sf::Vector2f& maxVel_ = sf::Vector2f{0.f, 200.f}, float sizeMin_ = 1.f, float sizeMax_ = 2.f, int spriteCount_ = 20, const sf::Color& colorTint_ = sf::Color{180, 180, 200, 125});
            void SetAssets(const List<std::string>& assetsPaths_);
            void SetColorTint(const sf::Color& color_);
            void SetSpriteCount(int newCount_);
            void SetVelocities(const sf::Vector2f& min_, const sf::Vector2f& max_);
            void SetSizes(float min_, float max_);
            virtual void Render(sf::RenderWindow& windowRef_) override;
            virtual void Tick(float deltaTime_) override;

        private:
            void RefreshSprites();
            void RandomSpriteTexture(sf::Sprite& sprite_);
            shared<sf::Texture> GetRandomTexture() const;
            void RandomSpriteTransform(sf::Sprite& sprite_, bool randomY_ = false);
            void RandomSpritePosition(sf::Sprite& sprite_, bool randomY_);
            void RandomSpriteRotation(sf::Sprite& sprite_);
            void RandomSpriteSize(sf::Sprite& sprite_);
            bool IsSpriteOfScreen(sf::Sprite& sprite_);
            sf::Vector2f mMinVelocity;
            sf::Vector2f mMaxVelocity;
            float mSizeMin;
            float mSizeMax;
            int mSpriteCount;
            sf::Color mTintColor;
            List<shared<sf::Texture>> mTextures;
            List<sf::Sprite> mSprites;
            List<sf::Vector2f> mVelocities;
    };
}  // namespace ly
