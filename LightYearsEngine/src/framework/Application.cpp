#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
        : mWindow{sf::VideoMode(windowWidth, windowHeight), title, style},
        mTargetFrameRate{60.f},
        mTickClock{},
        currentWorld{nullptr},
        mCleanCycleClock{sf::Clock{}},
        mCleanCycleInterval{2.f}
    {

    }


    void Application::Run()
    {
        mTickClock.restart();
        float _accumulatedTime{0.f};
        float _targetDeltaTime{1.f / mTargetFrameRate};
        while(mWindow.isOpen())
        {
            sf::Event _windowEvent;
            if(mWindow.pollEvent(_windowEvent))
            {
                if(_windowEvent.type == sf::Event::EventType::Closed)
                {
                    mWindow.close();
                }
            }
            _accumulatedTime += mTickClock.restart().asSeconds();
            if(_accumulatedTime > _targetDeltaTime)
            {
                _accumulatedTime -= _targetDeltaTime;
                TickInternal(_targetDeltaTime);
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

        if(currentWorld)
        {
            currentWorld->TickInternal(deltaTime_);
        }

        TimerManager::Get().UpdateTimer(deltaTime_);

        PhysicsSystem::Get().Step(deltaTime_);

        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if(currentWorld)
            {
                currentWorld->CleanCycle();
            }
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
        if(currentWorld)
        {
            currentWorld->Render(mWindow);
        }
    }

    void Application::Tick(float deltaTime_)
    {
        // LOG("ticking at frame rate: %f", 1.f / deltaTime_);
    }

    Application::~Application()
    {
        LOG("Application destroyed");
    }

} // namespace ly
