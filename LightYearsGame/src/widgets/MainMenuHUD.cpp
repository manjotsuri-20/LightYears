#include "widgets/MainMenuHUD.h"

namespace ly
{
    MainMenuHUD::MainMenuHUD()
        : mTitleText{"Lightyears"}
        , mStartButton{"Start"}
        , mQuitButton{"Quit"}
    {
        mTitleText.SetTextSize(40);
        mStartButton.SetTextSize(20);
        mQuitButton.SetTextSize(20);
    }

    void MainMenuHUD::Draw(sf::RenderWindow& windowRef_)
    {
        mTitleText.NativeDraw(windowRef_);
        mStartButton.NativeDraw(windowRef_);
        mQuitButton.NativeDraw(windowRef_);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event& event_)
    {
        return mStartButton.HandleEvent(event_) || mQuitButton.HandleEvent(event_) || HUD::HandleEvent(event_);
    }

    void MainMenuHUD::Init(const sf::RenderWindow& windowRef_)
    {
        sf::Vector2u _windowSize = windowRef_.getSize();
        mTitleText.SetWidgetLocation({_windowSize.x / 2.f - mTitleText.GetBound().width / 2.f, 100.f});

        mStartButton.SetWidgetLocation({_windowSize.x / 2.f - mStartButton.GetBound().width / 2.f, _windowSize.y / 2.f});
        mQuitButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{0.f, 50.f});

        mStartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
        mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
    }

    void MainMenuHUD::StartButtonClicked()
    {
        onStartButtonClicked.Broadcast();
    }

    void MainMenuHUD::QuitButtonClicked()
    {
        onQuitButtonClicked.Broadcast();
    }
}  // namespace ly
