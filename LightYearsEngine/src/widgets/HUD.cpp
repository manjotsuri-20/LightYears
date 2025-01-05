#include "widgets/HUD.h"

namespace ly
{
    void HUD::NativeInit(const sf::RenderWindow& windowRef_)
    {
        if (!mAlreadyInit)
        {
            Init(windowRef_);
            mAlreadyInit = true;
        }
    }

    bool HUD::HandleEvent(const sf::Event& event_)
    {
        return false;
    }

    void HUD::Tick(float deltaTime_)
    {
    }

    HUD::HUD()
        : mAlreadyInit{false}
    {
    }

    void HUD::Init(const sf::RenderWindow& windowRef_)
    {
    }

    void HUD::GameFinished(bool playerWon_)
    {
    }
}  // namespace ly
