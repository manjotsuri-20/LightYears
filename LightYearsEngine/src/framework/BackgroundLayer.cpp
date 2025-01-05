#include "framework/BackgroundLayer.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{

    BackgroundLayer::BackgroundLayer(World* owningWorld_, const List<std::string>& assetpaths_, const sf::Vector2f& minVel_, const sf::Vector2f& maxVel_, float sizeMin_, float sizeMax_, int spriteCount_, const sf::Color& colorTint_)
        : Actor{owningWorld_}
        , mMinVelocity{minVel_}
        , mMaxVelocity{maxVel_}
        , mSizeMin{sizeMin_}
        , mSizeMax{sizeMax_}
        , mSpriteCount{spriteCount_}
        , mTintColor{colorTint_}
    {
        SetAssets(assetpaths_);
        SetEnablePhysics(false);
    }

    void BackgroundLayer::Render(sf::RenderWindow& windowRef_)
    {
        Actor::Render(windowRef_);
        for (const sf::Sprite& _sprite : mSprites)
        {
            windowRef_.draw(_sprite);
        }
    }

    void BackgroundLayer::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);
        for (int i = 0; i < mSprites.size(); i++)
        {
            sf::Sprite& _sprite = mSprites[i];
            sf::Vector2f _vel = mVelocities[i];

            _sprite.setPosition(_sprite.getPosition() + _vel * deltaTime_);
            if (IsSpriteOfScreen(_sprite))
            {
                RandomSpriteTexture(_sprite);
                RandomSpriteTransform(_sprite);
                SetVelocities(mMinVelocity, mMaxVelocity);
            }
        }
    }

    void BackgroundLayer::SetAssets(const List<std::string>& assetsPaths_)
    {
        for (const std::string& _texturePath : assetsPaths_)
        {
            shared<sf::Texture> _newTexture = AssetManager::Get().LoadTexture(_texturePath);
            mTextures.push_back(_newTexture);
        }
        RefreshSprites();
    }

    void BackgroundLayer::RefreshSprites()
    {
        mSprites.clear();
        mVelocities.clear();

        for (int i = 0; i < mSpriteCount; i++)
        {
            sf::Sprite _newSprite{};
            RandomSpriteTexture(_newSprite);
            RandomSpriteTransform(_newSprite, true);
            mSprites.push_back(_newSprite);

            float _velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
            float _velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
            mVelocities.push_back(sf::Vector2f{_velX, _velY});
        }
        SetColorTint(mTintColor);
    }

    void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite_)
    {
        if (mTextures.size() > 0)
        {
            shared<sf::Texture> _pickedTexture = GetRandomTexture();
            sprite_.setTexture(*(_pickedTexture.get()));
            sprite_.setTextureRect(sf::IntRect{0, 0, (int)_pickedTexture->getSize().x, (int)_pickedTexture->getSize().y});
            sf::FloatRect _bound = sprite_.getGlobalBounds();
            sprite_.setOrigin(_bound.width / 2.f, _bound.height / 2.f);
        }
    }

    shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
    {
        int _randomPickIndex = (int)RandomRange(0, mTextures.size());
        return mTextures[_randomPickIndex];
    }

    void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite_, bool randomY_)
    {
        RandomSpritePosition(sprite_, randomY_);
        RandomSpriteRotation(sprite_);
        RandomSpriteSize(sprite_);
    }

    void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite_, bool randomY_)
    {
        auto _windowSize = GetWorld()->GetWindowSize();
        auto _bound = GetSprite().getGlobalBounds();

        float _posX = RandomRange(0, _windowSize.x);
        float _posY = randomY_ ? RandomRange(0, _windowSize.y) : -_bound.height;

        sprite_.setPosition(sf::Vector2f{_posX, _posY});
    }

    void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite_)
    {
        sprite_.setRotation(RandomRange(0, 360.f));
    }

    void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite_)
    {
        float _size = RandomRange(mSizeMin, mSizeMax);
        sprite_.setScale(_size, _size);
    }

    void BackgroundLayer::SetColorTint(const sf::Color& color_)
    {
        mTintColor = color_;
        for (sf::Sprite& _sprite : mSprites)
        {
            _sprite.setColor(mTintColor);
        }
    }

    void BackgroundLayer::SetSpriteCount(int newCount_)
    {
        mSpriteCount = newCount_;
        RefreshSprites();
    }

    bool BackgroundLayer::IsSpriteOfScreen(sf::Sprite& sprite_)
    {
        auto _bound = sprite_.getGlobalBounds();
        auto _windowSize = GetWorld()->GetWindowSize();
        auto _spritePos = sprite_.getPosition();

        if (_spritePos.x < -_bound.width || _spritePos.x > _windowSize.x + _bound.width)
        {
            return true;
        }

        if (_spritePos.y < -_bound.height || _spritePos.y > _windowSize.y + _bound.height)
        {
            return true;
        }
        return false;
    }

    void BackgroundLayer::SetVelocities(const sf::Vector2f& min_, const sf::Vector2f& max_)
    {
        mMinVelocity = min_;
        mMaxVelocity = max_;

        for (int i = 0; i < mSprites.size(); i++)
        {
            float _velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
            float _velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
            mVelocities[i] = sf::Vector2f{_velX, _velY};
        }
    }

    void BackgroundLayer::SetSizes(float min_, float max_)
    {
        mSizeMin = min_;
        mSizeMax = max_;

        for (int i = 0; i < mSprites.size(); i++)
        {
            RandomSpriteSize(mSprites[i]);
        }
    }
}  // namespace ly
