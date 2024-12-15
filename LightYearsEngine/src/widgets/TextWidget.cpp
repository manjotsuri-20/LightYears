#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
    TextWidget::TextWidget(const std::string& textStr_, const std::string& fontPath_, unsigned int characterSize_)
        : mFont{AssetManager::Get().LoadFont(fontPath_)}, 
        mText{textStr_, *mFont.get(), characterSize_}
    {}

    void TextWidget::SetString(const std::string &newstring_)
    {
        mText.setString(newstring_);
    }

    void TextWidget::SetTextSize(unsigned int newSize_)
    {
        mText.setCharacterSize(newSize_);
    }

    sf::FloatRect TextWidget::GetBound() const
    {
        return mText.getGlobalBounds();
    }

    void TextWidget::LocationUpdated(const sf::Vector2f &newLocation_)
    {
        mText.setPosition(newLocation_);
    }

    void TextWidget::RotationUpdated(float newRotation_)
    {
        mText.setRotation(newRotation_);
    }

    void TextWidget::Draw(sf::RenderWindow &windowRef_)
    {
        windowRef_.draw(mText);
    }

} // namespace ly
