#include "widgets/GameplayHUD.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame Rate:"},
        mPlayerHealthBar{},
        mHealthyHealthBarColor{128, 255, 128, 255},
        mCriticalHealthBarColor{128, 0, 0, 255},
        mCriticalThreshould{0.3f}
    {
        mFramerateText.SetTextSize(30);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef_)
    {
        mFramerateText.NativeDraw(windowRef_);
        mPlayerHealthBar.NativeDraw(windowRef_);
    }

    void GameplayHUD::Tick(float deltaTime_)
    {
        int _frameRate = int(1 / deltaTime_);
        std::string _frameRateString = "Frame Rate: " + std::to_string(_frameRate);
        mFramerateText.SetString(_frameRateString);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef_)
    {
        auto _windowSize = windowRef_.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{10.f, _windowSize.y - 50.f});

        RefreshHealthBar();
    }

    void GameplayHUD::PlayerHealthUpdated(float amt_, float currentHealth_, float maxHealth_)
    {
        UpdateHealthBar(currentHealth_, maxHealth_);
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor_)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player* _player = PlayerManager::Get().GetPlayer();
        if(_player && !_player->GetCurrentSpaceship().expired())
        {
            weak<PlayerSpaceship> _playerSpaceship = _player->GetCurrentSpaceship();
            _playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);

            HealthComponent& _healthComp = _player->GetCurrentSpaceship().lock()->GetHealthComp();
            _healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
            UpdateHealthBar(_healthComp.GetHealth(), _healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::UpdateHealthBar(float currHealth_, float maxHealth_)
    {
        mPlayerHealthBar.UpdateValue(currHealth_, maxHealth_);
        if(currHealth_ / maxHealth_ < mCriticalThreshould)
        {
            mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
        }
        else
        {
            mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
        }
    }
} // namespace ly

