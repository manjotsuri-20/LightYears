#include "widgets/Widget.h"

namespace ly
{
    Widget::Widget()
        : mIsVisible{true},
        mWidgetTransfrom{}
    {}

    void Widget::NativeDraw(sf::RenderWindow& windowRef_)
    {
        if(mIsVisible)
        {
            Draw(windowRef_);
        }
    }

    bool Widget::HandleEvent(const sf::Event& event_)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const sf::Vector2f& newLocation_)
    {
        mWidgetTransfrom.setPosition(newLocation_);
        LocationUpdated(newLocation_);
    }

    void Widget::SetWidgetRotation(float newRotation_)
    {
        mWidgetTransfrom.setRotation(newRotation_);
        RotationUpdated(newRotation_);
    }

    void Widget::SetVisibility(bool newVisibility_)
    {
        mIsVisible = newVisibility_;
    }

    sf::FloatRect Widget::GetBound() const
    {
        return sf::FloatRect();
    }

    sf::Vector2f Widget::GetCentrePosition() const
    {
        sf::FloatRect _bound = GetBound();
        return sf::Vector2f{_bound.left + _bound.width/2.f, _bound.top + _bound.height/2.f};
    }

    void Widget::Draw(sf::RenderWindow &windowRef_)
    {}

    void Widget::LocationUpdated(const sf::Vector2f& newLocation_)
    {}

    void Widget::RotationUpdated(float newRotation_)
    {}
    
} // namespace ly
