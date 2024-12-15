#pragma once
#include "widgets/HUD.h"
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

        private:
            virtual void Init(const sf::RenderWindow& windowRef_) override;
            void PlayerHealthUpdated(float amt_, float currentHealth_, float maxHealth_);
            void PlayerSpaceshipDestroyed(Actor* actor_);
            void RefreshHealthBar();
            void UpdateHealthBar(float currHealth_, float maxHealth_);
            TextWidget mFramerateText;
            ValueGauge mPlayerHealthBar;

            sf::Color mHealthyHealthBarColor;
            sf::Color mCriticalHealthBarColor;
            float mCriticalThreshould;
    };

} // namespace ly