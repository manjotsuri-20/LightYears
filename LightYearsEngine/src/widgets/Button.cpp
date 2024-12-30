#include "widgets/Button.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "framework/AssetManager.h"

namespace ly
{
    Button::Button(const std::string& textString_, const std::string& buttonTexturePath_)
        : mButtonTexture{AssetManager::Get().LoadTexture(buttonTexturePath_)}
        , mButtonSprite{*(mButtonTexture.get())}
        , mButtonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")}
        , mButtonText{textString_, *(mButtonFont.get())}
        , mButtonDefaultColor{128, 128, 128, 255}
        , mButtonDownColor{64, 64, 64, 255}
        , mButtonHoverColor{190, 190, 190, 255}
        , mIsButtonDown{false}
    {
        mButtonSprite.setColor(mButtonDefaultColor);
        CenterText();
    }

    void Button::Draw(sf::RenderWindow& windowRef_)
    {
        windowRef_.draw(mButtonSprite);
        windowRef_.draw(mButtonText);
    }

    void Button::LocationUpdated(const sf::Vector2f& location_)
    {
        mButtonSprite.setPosition(location_);
        CenterText();
    }

    void Button::RotationUpdated(float rotation_)
    {
        mButtonSprite.setRotation(rotation_);
        mButtonText.setRotation(rotation_);
    }

    sf::FloatRect Button::GetBound() const
    {
        return mButtonSprite.getGlobalBounds();
    }

    void Button::CenterText()
    {
        sf::Vector2f _widgetCentre = GetCentrePosition();
        sf::FloatRect _textBound = mButtonText.getGlobalBounds();
        mButtonText.setPosition(_widgetCentre - sf::Vector2f{_textBound.width / 2.f, _textBound.height});
    }

    void Button::setTextString(const std::string& newString_)
    {
        mButtonText.setString(newString_);
    }

    void Button::SetTextSize(unsigned int characterSize_)
    {
        mButtonText.setCharacterSize(characterSize_);
        CenterText();
    }

    bool Button::HandleEvent(const sf::Event& event_)
    {
        bool _handled = false, _result = false;

        if (event_.type == sf::Event::MouseButtonReleased)
        {
            if (event_.mouseButton.button == sf::Mouse::Left)
            {
                if (mButtonSprite.getGlobalBounds().contains(event_.mouseButton.x, event_.mouseButton.y) && mIsButtonDown)
                {
                    onButtonClicked.Broadcast();
                    _handled = true;
                }
            }
            ButtonUp();
        }
        else if (event_.type == sf::Event::MouseButtonPressed)
        {
            if (mButtonSprite.getGlobalBounds().contains(event_.mouseButton.x, event_.mouseButton.y))
            {
                ButtonDown();
                _handled = true;
            }
        }
        else if (event_.type == sf::Event::MouseMoved)
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (mButtonSprite.getGlobalBounds().contains(event_.mouseMove.x, event_.mouseMove.y))
                {
                    ButtonHower();
                }
                else
                {
                    ButtonUp();
                }
                _handled = true;
            }
        }

        _result = Widget::HandleEvent(event_) || _handled;
        return _result;
    }

    void Button::ButtonUp()
    {
        mIsButtonDown = false;
        mButtonSprite.setColor(mButtonDefaultColor);
    }

    void Button::ButtonDown()
    {
        mIsButtonDown = true;
        mButtonSprite.setColor(mButtonDownColor);
    }

    void Button::ButtonHower()
    {
        mButtonSprite.setColor(mButtonHoverColor);
    }
}  // namespace ly
