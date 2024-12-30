#include "widgets/GameplayHUD.h"

#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame Rate:"}
        , mPlayerHealthBar{}
        , mPlayerLifeIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"}
        , mPlayerLifeText{""}
        , mPlayerScoreIcon{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"}
        , mPlayerScoreText{""}
        , mHealthyHealthBarColor{128, 255, 128, 255}
        , mCriticalHealthBarColor{128, 0, 0, 255}
        , mCriticalThreshould{0.3f}
        , mWidgetSpacing{10.f}
    {
        mFramerateText.SetTextSize(30);
        mPlayerLifeText.SetTextSize(20);
        mPlayerScoreText.SetTextSize(20);
    }

    void GameplayHUD::Draw(sf::RenderWindow& windowRef_)
    {
        mFramerateText.NativeDraw(windowRef_);
        mPlayerHealthBar.NativeDraw(windowRef_);
        mPlayerLifeIcon.NativeDraw(windowRef_);
        mPlayerLifeText.NativeDraw(windowRef_);
        mPlayerScoreIcon.NativeDraw(windowRef_);
        mPlayerScoreText.NativeDraw(windowRef_);
    }

    void GameplayHUD::Tick(float deltaTime_)
    {
        int _frameRate = int(1 / deltaTime_);
        std::string _frameRateString = "Frame Rate: " + std::to_string(_frameRate);
        mFramerateText.SetString(_frameRateString);
    }

    void GameplayHUD::Init(const sf::RenderWindow& windowRef_)
    {
        auto _windowSize = windowRef_.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{10.f, _windowSize.y - 50.f});

        sf::Vector2f _nextWidgetLoc = mPlayerHealthBar.GetWidgetLocation();
        _nextWidgetLoc += sf::Vector2f{mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeIcon.SetWidgetLocation(_nextWidgetLoc);

        _nextWidgetLoc += sf::Vector2f{mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeText.SetWidgetLocation(_nextWidgetLoc);

        _nextWidgetLoc += sf::Vector2f{mPlayerLifeText.GetBound().width + mWidgetSpacing * 4, -4.f};
        mPlayerScoreIcon.SetWidgetLocation(_nextWidgetLoc);

        _nextWidgetLoc += sf::Vector2f{mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 4.f};
        mPlayerScoreText.SetWidgetLocation(_nextWidgetLoc);

        RefreshHealthBar();
        ConnectPlayerStatus();
    }

    void GameplayHUD::PlayerHealthUpdated(float amt_, float currentHealth_, float maxHealth_)
    {
        UpdateHealthBar(currentHealth_, maxHealth_);
    }

    void GameplayHUD::PlayerLifeCountUpdated(int amt_)
    {
        mPlayerLifeText.SetString(std::to_string(amt_));
    }

    void GameplayHUD::PlayerScoreUpdated(int newScore_)
    {
        mPlayerScoreText.SetString(std::to_string(newScore_));
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor_)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player* _player = PlayerManager::Get().GetPlayer();
        if (_player && !_player->GetCurrentSpaceship().expired())
        {
            weak<PlayerSpaceship> _playerSpaceship = _player->GetCurrentSpaceship();
            _playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);

            HealthComponent& _healthComp = _player->GetCurrentSpaceship().lock()->GetHealthComp();
            _healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
            PlayerHealthUpdated(0, _healthComp.GetHealth(), _healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::ConnectPlayerStatus()
    {
        Player* _player = PlayerManager::Get().GetPlayer();
        if (_player)
        {
            int _lifeCount = _player->GetLifeCount();
            mPlayerLifeText.SetString(std::to_string(_lifeCount));
            _player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

            int _playerScore = _player->GetScore();
            mPlayerScoreText.SetString(std::to_string(_playerScore));
            _player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
        }
    }

    void GameplayHUD::UpdateHealthBar(float currHealth_, float maxHealth_)
    {
        mPlayerHealthBar.UpdateValue(currHealth_, maxHealth_);
        if (currHealth_ / maxHealth_ < mCriticalThreshould)
        {
            mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
        }
        else
        {
            mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
        }
    }

    bool GameplayHUD::HandleEvent(const sf::Event& event_)
    {
        return HUD::HandleEvent(event_);
    }
}  // namespace ly
