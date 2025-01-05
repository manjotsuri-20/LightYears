#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Object.h"

namespace ly
{
    class HUD : public Object
    {
        public:
            virtual void Draw(sf::RenderWindow& windowRef_) = 0;
            void NativeInit(const sf::RenderWindow& windowRef_);
            bool HasInit()
            {
                return mAlreadyInit;
            }
            virtual bool HandleEvent(const sf::Event& event_);
            virtual void Tick(float deltaTime_);
            virtual void GameFinished(bool playerWon_);

        protected:
            HUD();

        private:
            virtual void Init(const sf::RenderWindow& windowRef_);
            bool mAlreadyInit;
    };
}  // namespace ly
