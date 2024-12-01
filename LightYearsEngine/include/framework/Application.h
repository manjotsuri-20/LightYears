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

            template<typename WorldType>
            weak<WorldType> LoadWorld();

        private:

            void TickInternal(float delta_time_);
            void RenderInternal();

            virtual void Tick(float deltaTime_);
            virtual void Render();

            sf::RenderWindow mWindow;
            float mTargetFrameRate{-1};
            sf::Clock mTickClock;

            shared<World> currentWorld;
            sf::Clock mCleanCycleClock;
            float mCleanCycleInterval;
    };

    template<typename WorldType>
    inline weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType{this}};
        currentWorld = newWorld;
        currentWorld->BeginPlayInternal();
        return newWorld;
    }
}