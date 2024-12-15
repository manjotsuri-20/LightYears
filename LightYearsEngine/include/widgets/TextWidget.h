#pragma once
#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
    class TextWidget: public Widget
    {
        public: 
            TextWidget(const std::string& textStr_, 
                const std::string& fontPath_ = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
                unsigned int characterSize_ = 10
                );

            void SetString(const std::string& newstring_);
            void SetTextSize(unsigned int newSize_);
            virtual sf::FloatRect GetBound() const override;

        private:
            virtual void LocationUpdated(const sf::Vector2f& newLocation_) override;
            virtual void RotationUpdated(float newRotation_) override;
            virtual void Draw(sf::RenderWindow& windowRef_) override;

            shared<sf::Font> mFont; 
            sf::Text mText;
    };
} // namespace ly
