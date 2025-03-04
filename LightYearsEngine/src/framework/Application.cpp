#include "framework/Application.h"

#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
        : mWindow{sf::VideoMode(windowWidth, windowHeight), title, style}
        , mTargetFrameRate{120.f}
        , mTickClock{}
        , mCurrentWorld{nullptr}
        , mCleanCycleClock{sf::Clock{}}
        , mCleanCycleInterval{2.f}
        , mGamePaused{false}
    {
    }

    void Application::Run()
    {
        mTickClock.restart();
        float _accumulatedTime{0.f};
        float _targetDeltaTime{1.f / mTargetFrameRate};
        while (mWindow.isOpen())
        {
            sf::Event _windowEvent;
            if (mWindow.pollEvent(_windowEvent))
            {
                if (_windowEvent.type == sf::Event::EventType::Closed)
                {
                    QuitApplication();
                }
                else
                {
                    DispatchEvent(_windowEvent);
                }
            }
            _accumulatedTime += mTickClock.restart().asSeconds();
            if (_accumulatedTime > _targetDeltaTime)
            {
                TickInternal(_targetDeltaTime);  // don't pass accumulated time becuse sometimes it takes time to render window because of which behaviour of game is weired // pass accumulated time instead of delta time so as to run the loop according to the actual time passed
                _accumulatedTime -= _targetDeltaTime;
                RenderInternal();
            }
        }
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }

    void Application::TickInternal(float deltaTime_)
    {
        Tick(deltaTime_);

        if (!mGamePaused)
        {

            if (mCurrentWorld)
            {
                mCurrentWorld->TickInternal(deltaTime_);
            }

            TimerManager::Get().UpdateTimer(deltaTime_);

            PhysicsSystem::Get().Step(deltaTime_);
        }

        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if (mCurrentWorld)
            {
                mCurrentWorld->CleanCycle();
            }
        }

        if (mPendingWorld && mPendingWorld != mCurrentWorld)
        {
            mCurrentWorld = mPendingWorld;
            PhysicsSystem::Get().Cleanup();
            mCurrentWorld->BeginPlayInternal();
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application::Render()
    {
        if (mCurrentWorld)
        {
            mCurrentWorld->Render(mWindow);
        }
    }

    void Application::Tick(float deltaTime_)
    {
        // LOG("ticking at frame rate: %f", 1.f / deltaTime_);
    }

    bool Application::DispatchEvent(const sf::Event& event_)
    {
        if (mCurrentWorld)
        {
            return mCurrentWorld->DispatchEvent(event_);
        }
        return false;
    }

    Application::~Application()
    {
        LOG("Application destroyed");
    }

    void Application::QuitApplication()
    {
        mWindow.close();
    }

    void Application::PauseGame(bool val_)
    {
        mGamePaused = val_;
    }

}  // namespace ly
