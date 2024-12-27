#pragma once
#include "widgets/Widget.h"

namespace ly
{
    class ImageWidget : public Widget
    {
        public:
            ImageWidget(const std::string& imagePath_);

            void SetImage(const shared<sf::Texture>& newTexture_);
            virtual sf::FloatRect GetBound() const override;

        private:
            virtual void LocationUpdated(const sf::Vector2f& newLocation_);
            virtual void RotationUpdated(float newRotation_);
            virtual void Draw(sf::RenderWindow& windowRef_) override;
            shared<sf::Texture> mTexture;
            sf::Sprite mSprite;
    };
} // namespace ly
