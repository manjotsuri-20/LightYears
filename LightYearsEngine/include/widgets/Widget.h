#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Widget : public Object
    {
        public:
            void NativeDraw(sf::RenderWindow& windowRef_);
            virtual bool HandleEvent(const sf::Event& event_);
            void SetWidgetLocation(const sf::Vector2f& newLocation_);
            void SetWidgetRotation(float newRotation_);
            const sf::Vector2f& GetWidgetLocation() const { return mWidgetTransfrom.getPosition(); }
            float GetWidgetRotation() const { return mWidgetTransfrom.getRotation(); }
            void SetVisibility(bool newVisibility_);
            bool GetVisibility() const { return mIsVisible; }
            virtual sf::FloatRect GetBound() const = 0;
            sf::Vector2f GetCentrePosition() const;

        protected:
            Widget();

        private:
            virtual void Draw(sf::RenderWindow& windowRef_);
            virtual void LocationUpdated(const sf::Vector2f& newLocation_);
            virtual void RotationUpdated(float newRotation_);
            sf::Transformable mWidgetTransfrom;
            bool mIsVisible;
    };
} // namespace ly
