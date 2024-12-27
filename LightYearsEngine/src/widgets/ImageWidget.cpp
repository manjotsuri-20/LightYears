#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
    ImageWidget::ImageWidget(const std::string& imagePath_)
        : mTexture{AssetManager::Get().LoadTexture(imagePath_)},
        mSprite{*(mTexture.get())}
    {}

    void ImageWidget::SetImage(const shared<sf::Texture> &newTexture_)
    {
        if(newTexture_)
        {
            mTexture = newTexture_;
            mSprite.setTexture(*mTexture.get());
        }
    }

    sf::FloatRect ImageWidget::GetBound() const
    {
        return mSprite.getGlobalBounds();
    }

    void ImageWidget::LocationUpdated(const sf::Vector2f &newLocation_)
    {
        mSprite.setPosition(newLocation_);
    }

    void ImageWidget::RotationUpdated(float newRotation_)
    {
        mSprite.setRotation(newRotation_);
    }

    void ImageWidget::Draw(sf::RenderWindow &windowRef_)
    {
        windowRef_.draw(mSprite);
    }
} // namespace ly
