#pragma once
#include "widgets/Button.h"
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    class Actor;
    class GameplayHUD : public HUD
    {
        public:
            GameplayHUD();
            virtual void Draw(sf::RenderWindow& windowRef_) override;
            virtual void Tick(float deltaTime_) override;
            virtual bool HandleEvent(const sf::Event& event_) override;

        private:
            virtual void Init(const sf::RenderWindow& windowRef_) override;
            void PlayerHealthUpdated(float amt_, float currentHealth_, float maxHealth_);
            void PlayerLifeCountUpdated(int amt_);
            void PlayerScoreUpdated(int newScore_);
            void PlayerSpaceshipDestroyed(Actor* actor_);
            void RefreshHealthBar();
            void ConnectPlayerStatus();
            void UpdateHealthBar(float currHealth_, float maxHealth_);
            TextWidget mFramerateText;
            ValueGauge mPlayerHealthBar;
            ImageWidget mPlayerLifeIcon;
            TextWidget mPlayerLifeText;
            ImageWidget mPlayerScoreIcon;
            TextWidget mPlayerScoreText;

            sf::Color mHealthyHealthBarColor;
            sf::Color mCriticalHealthBarColor;
            float mCriticalThreshould;

            float mWidgetSpacing;
    };

}  // namespace ly
