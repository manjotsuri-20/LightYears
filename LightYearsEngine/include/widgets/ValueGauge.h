#pragma once
#include "widgets/Widget.h"

namespace ly
{
    class ValueGauge : public Widget
    {
        public:
            ValueGauge(const sf::Vector2f& size_ = sf::Vector2f{200.f, 30.f}, 
                float initialPercent_ = 0.75f, 
                const sf::Color& foregroundColor_ = sf::Color{128, 255, 128, 255}, 
                const sf::Color& backgroundColor_ = sf::Color{128, 128, 128, 255}
                );
            void UpdateValue(float value_, float maxValue_);
            virtual sf::FloatRect GetBound() const override;
            void SetTextSize(unsigned int characterSize_);
            void SetForegroundColor(const sf::Color& color_);
            void SetBackgroundColor(const sf::Color& color_);

        private:
            virtual void LocationUpdated(const sf::Vector2f& newLocation_) override;
            virtual void RotationUpdated(float newRotation_) override;
            virtual void Draw(sf::RenderWindow& windowRef_) override;
            void CenterText();
            shared<sf::Font> mTextFont;
            sf::Text mText;

            sf::RectangleShape mBarFront;
            sf::RectangleShape mBarBack;

            sf::Color mForegroundColor;
            sf::Color mBackgroundColor;

            float mPercent;
    };
} // namespace ly
