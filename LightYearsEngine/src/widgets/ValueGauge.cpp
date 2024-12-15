#include "widgets/ValueGauge.h"
#include "framework/AssetManager.h"

namespace ly
{
    ValueGauge::ValueGauge(const sf::Vector2f &size_, float initialPercent_, const sf::Color& foregroundColor_, const sf::Color& backgroundColor_)
        : mTextFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")}, 
        mText{"", *mTextFont.get()},
        mBarFront{size_},
        mBarBack{size_},
        mForegroundColor{foregroundColor_},
        mBackgroundColor{backgroundColor_},
        mPercent{initialPercent_}
    {
        mBarFront.setFillColor(mForegroundColor);
        mBarBack.setFillColor(mBackgroundColor);
        SetTextSize(20);
    }

    void ValueGauge::UpdateValue(float value_, float maxValue_)
    {
        if(maxValue_ == 0) return;
        mPercent = value_ / maxValue_;
        std::string _displayString = std::to_string((int)value_) + "/" + std::to_string((int)maxValue_);
        mText.setString(_displayString);

        sf::Vector2f _barSize = mBarBack.getSize();
        mBarFront.setSize({_barSize.x * mPercent, _barSize.y});
        CenterText();
    }

    void ValueGauge::LocationUpdated(const sf::Vector2f &newLocation_)
    {
        mBarFront.setPosition(newLocation_);
        mBarBack.setPosition(newLocation_);
        CenterText();
    }

    void ValueGauge::RotationUpdated(float newRotation_)
    {
        mText.setRotation(newRotation_);
        mBarFront.setRotation(newRotation_);
        mBarBack.setRotation(newRotation_);
    }

    void ValueGauge::Draw(sf::RenderWindow &windowRef_)
    {
        windowRef_.draw(mBarBack);
        windowRef_.draw(mBarFront);
        windowRef_.draw(mText);
    }

    sf::FloatRect ValueGauge::GetBound() const
    {
        return mBarBack.getGlobalBounds();
    }

    void ValueGauge::SetTextSize(unsigned int characterSize_)
    {
        mText.setCharacterSize(characterSize_);
    }

    void ValueGauge::SetForegroundColor(const sf::Color &color_)
    {
        mBarFront.setFillColor(color_);
    }

    void ValueGauge::SetBackgroundColor(const sf::Color &color_)
    {
        mBarBack.setFillColor(color_);
    }

    void ValueGauge::CenterText()
    {
        sf::Vector2f _widgetCentre = GetCentrePosition();
        sf::FloatRect _textBound = mText.getGlobalBounds();
        mText.setPosition(_widgetCentre - sf::Vector2f{_textBound.width/2.f, _textBound.height});
    }
} // namespace ly

