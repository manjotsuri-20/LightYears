#pragma once

#include "framework/Delegate.h"
#include "widgets/Button.h"
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"

namespace ly
{
    class MainMenuHUD : public HUD
    {
        public:
            MainMenuHUD();
            virtual void Draw(sf::RenderWindow& windowRef_) override;
            virtual bool HandleEvent(const sf::Event& event_) override;
            Delegate<> onStartButtonClicked;
            Delegate<> onQuitButtonClicked;

        private:
            virtual void Init(const sf::RenderWindow& windowRef_) override;
            void StartButtonClicked();
            void QuitButtonClicked();
            TextWidget mTitleText;
            Button mStartButton;
            Button mQuitButton;
    };
}  // namespace ly
