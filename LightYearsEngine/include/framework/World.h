#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    class Actor;
    class Application;
    class GameStage;
    class HUD;
    class World : public Object
    {
        public:
            World(Application* owningApp);

            void BeginPlayInternal();

            void TickInternal(float deltaTime_);

            virtual ~World();

            template <typename ActorType, typename... Args>
            weak<ActorType> SpawnActor(Args... args_);

            template <typename HUDType, typename... Args>
            weak<HUDType> SpawnHUD(Args... args_);

            void Render(sf::RenderWindow& window_);

            sf::Vector2u GetWindowSize() const;

            void CleanCycle();
            void AddStage(const shared<GameStage>& newStage_);

            bool DispatchEvent(const sf::Event& event_);

            Application* GetApplication()
            {
                return mOwningApp;
            }

            const Application* GetApplication() const
            {
                return mOwningApp;
            }

        private:
            void RenderHUD(sf::RenderWindow& window_);
            virtual void BeginPlay();
            virtual void Tick(float deltaTime_);

            Application* mOwningApp;
            bool mBegunPlay{false};

            List<shared<Actor>> mActors;
            List<shared<Actor>> mPendingActors;
            List<shared<GameStage>> mGameStages;
            List<shared<GameStage>>::iterator mCurrentStage;

            shared<HUD> mHUD;

            virtual void InitGameStages();
            virtual void AllGameStageFinished();
            void NextGameStage();
            void StartStages();
    };

    template <typename ActorType, typename... Args>
    inline weak<ActorType> World::SpawnActor(Args... args_)
    {
        shared<ActorType> _newActor{new ActorType(this, args_...)};
        mPendingActors.push_back(_newActor);
        return _newActor;
    }

    template <typename HUDType, typename... Args>
    weak<HUDType> World::SpawnHUD(Args... args_)
    {
        shared<HUDType> _newHUD{new HUDType(args_...)};
        mHUD = _newHUD;
        return _newHUD;
    }
}  // namespace ly
