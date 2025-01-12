#include "widgets/GameplayHUD.h"

#include <string>

#include "SFML/System/Vector2.hpp"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/Button.h"

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
        , mPauseButtonText{"Pause"}
        , mResumeButtonText{"Resume"}
        , mCriticalThreshould{0.3f}
        , mWidgetSpacing{10.f}
        , mWinLoseText{""}
        , mFinalScoreText{""}
        , mRestartButton{"Restart"}
        , mQuitButton{"Quit"}
        , mPauseButton{"Pause"}
        , mWindowSize{}
    {
        mFramerateText.SetTextSize(30);
        mPlayerLifeText.SetTextSize(20);
        mPlayerScoreText.SetTextSize(20);

        mPauseButton.SetScale(sf::Vector2f{0.5f, 1.f});

        mPauseButtonColor.defaultColor = sf::Color{255, 0, 0, 255};
        mPauseButtonColor.downColor = sf::Color{50, 0, 0, 255};
        mPauseButtonColor.hoverColor = sf::Color{125, 0, 0, 225};
        mResumeButtonColor.defaultColor = sf::Color{0, 255, 0, 255};
        mResumeButtonColor.downColor = sf::Color{0, 50, 0, 255};
        mResumeButtonColor.hoverColor = sf::Color{0, 125, 0, 255};
        mPauseButton.SetColor(mPauseButtonColor);

        mWinLoseText.SetVisibility(false);
        mFinalScoreText.SetVisibility(false);
        mRestartButton.SetVisibility(false);
        mQuitButton.SetVisibility(false);
    }

    void GameplayHUD::Draw(sf::RenderWindow& windowRef_)
    {
        mWindowSize = windowRef_.getSize();
        mFramerateText.NativeDraw(windowRef_);
        mPlayerHealthBar.NativeDraw(windowRef_);
        mPlayerLifeIcon.NativeDraw(windowRef_);
        mPlayerLifeText.NativeDraw(windowRef_);
        mPlayerScoreIcon.NativeDraw(windowRef_);
        mPlayerScoreText.NativeDraw(windowRef_);
        mWinLoseText.NativeDraw(windowRef_);
        mFinalScoreText.NativeDraw(windowRef_);
        mRestartButton.NativeDraw(windowRef_);
        mQuitButton.NativeDraw(windowRef_);
        mPauseButton.NativeDraw(windowRef_);
    }

    void GameplayHUD::Tick(float deltaTime_)
    {
        int         _frameRate = int(1 / deltaTime_);
        std::string _frameRateString = "Frame Rate: " + std::to_string(_frameRate);
        mFramerateText.SetString(_frameRateString);
    }

    void GameplayHUD::Init(const sf::RenderWindow& windowRef_)
    {
        auto _windowSize = windowRef_.getSize();
        mWindowSize = _windowSize;
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

        mWinLoseText.SetTextSize(40.f);
        mWinLoseText.SetWidgetLocation({_windowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f});

        mFinalScoreText.SetTextSize(40.f);
        mFinalScoreText.SetWidgetLocation({_windowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f, 200.f});

        mRestartButton.SetWidgetLocation({_windowSize.x / 2.f - mRestartButton.GetBound().width / 2.f, _windowSize.y / 2.f});
        mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{0.f, 50.f});

        mPauseButton.SetTextSize(20.f);
        mPauseButton.SetWidgetLocation(sf::Vector2f{_windowSize.x - mPauseButton.GetBound().width - 10.f, 10.f});

        mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
        mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
        mPauseButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::PauseButtonClicked);
    }

    void GameplayHUD::RestartButtonClicked()
    {
        onRestartButtonClicked.Broadcast();
    }

    void GameplayHUD::QuitButtonClicked()
    {
        onQuitButtonClicked.Broadcast();
    }

    void GameplayHUD::PauseButtonClicked()
    {
        onPauseButtonClicked.Broadcast();
    }

    void GameplayHUD::UpdatePauseButtonStatus(bool status_)
    {
        ButtonColor _color;
        std::string _text;
        if (status_)
        {
            _color = mPauseButtonColor;
            _text = mPauseButtonText;
            mRestartButton.SetVisibility(false);
            mQuitButton.SetVisibility(false);
        }
        else
        {
            _color = mResumeButtonColor;
            _text = mResumeButtonText;
            mRestartButton.SetVisibility(true);
            mQuitButton.SetVisibility(true);
        }
        mPauseButton.SetColor(_color);
        mPauseButton.setTextString(_text);
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
        if (mRestartButton.HandleEvent(event_)) return true;
        if (mQuitButton.HandleEvent(event_)) return true;
        if (mPauseButton.HandleEvent(event_)) return true;
        return HUD::HandleEvent(event_);
    }

    void GameplayHUD::GameFinished(bool playerWon_)
    {
        mWinLoseText.SetVisibility(true);
        mFinalScoreText.SetVisibility(true);
        mRestartButton.SetVisibility(true);
        mQuitButton.SetVisibility(true);
        mPauseButton.SetVisibility(false);

        int _score = PlayerManager::Get().GetPlayer()->GetScore();
        mFinalScoreText.SetString("Score: " + std::to_string(_score));

        if (playerWon_)
        {
            mWinLoseText.SetString("You Won!");
        }
        else
        {
            mWinLoseText.SetString("You Lose!");
        }
        mWinLoseText.SetWidgetLocation({mWindowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f});
        mFinalScoreText.SetWidgetLocation({mWindowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f, 200.f});
    }
}  // namespace ly
