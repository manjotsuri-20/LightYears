#pragma once
#include <SFML/Graphics.hpp>
#include <framework/Core.h>

namespace ly
{
    class World;

    class Application
    {
        public:
            Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);

            virtual ~Application();

            void Run();

            sf::Vector2u GetWindowSize() const;

            sf::RenderWindow& GetWindow()
            {
                return mWindow;
            }

            const sf::RenderWindow& GetWindow() const
            {
                return mWindow;
            }

            template <typename WorldType>
            weak<WorldType> LoadWorld();

            void QuitApplication();

            void PauseGame(bool val_);

            bool GetGamePaused() const
            {
                return mGamePaused;
            }

        private:
            bool DispatchEvent(const sf::Event& event_);
            void TickInternal(float delta_time_);
            void RenderInternal();

            virtual void Tick(float deltaTime_);
            virtual void Render();

            sf::RenderWindow mWindow;
            float mTargetFrameRate{-1};
            sf::Clock mTickClock;

            shared<World> mCurrentWorld;
            shared<World> mPendingWorld;
            sf::Clock mCleanCycleClock;
            float mCleanCycleInterval;
            bool mGamePaused;
    };

    template <typename WorldType>
    inline weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType{this}};
        mPendingWorld = newWorld;
        // mCurrentWorld->BeginPlayInternal();
        return newWorld;
    }
}  // namespace ly
