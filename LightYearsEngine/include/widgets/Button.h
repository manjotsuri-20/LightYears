#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "framework/Delegate.h"
#include "widgets/Widget.h"

namespace ly
{
    struct ButtonColor
    {
        sf::Color defaultColor;
        sf::Color downColor;
        sf::Color hoverColor;
    };

    class Button : public Widget
    {
        public:
        Button(const std::string& textString_ = "Button", const std::string& buttonTexturePath_ = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
        virtual sf::FloatRect GetBound() const override;
        void                  setTextString(const std::string& newString_);
        void                  SetTextSize(unsigned int characterSize_);
        virtual bool          HandleEvent(const sf::Event& event_) override;
        Delegate<>            onButtonClicked;
        void                  SetScale(const sf::Vector2f& scaleVec_);
        void                  SetColor(const ButtonColor& color_);

        private:
        virtual void        Draw(sf::RenderWindow& windowRef_) override;
        virtual void        LocationUpdated(const sf::Vector2f& location_) override;
        virtual void        RotationUpdated(float rotation_) override;
        void                CenterText();
        void                ButtonUp();
        void                ButtonDown();
        void                ButtonHower();
        shared<sf::Texture> mButtonTexture;
        sf::Sprite          mButtonSprite;

        shared<sf::Font> mButtonFont;
        sf::Text         mButtonText;

        ButtonColor mButtonColor;

        bool mIsButtonDown;
    };
}  // namespace ly
