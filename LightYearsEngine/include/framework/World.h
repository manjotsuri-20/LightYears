#pragma once
#include "framework/Core.h"
#include "framework/Actor.h"
#include <SFML/Graphics.hpp>

namespace ly
{   
    class Actor;
    class Application;
    class GameStage;
    class World : public Object
    {
        public:

            World(Application* owningApp);

            void BeginPlayInternal();

            void TickInternal(float deltaTime_);

            virtual ~World();

            template<typename ActorType, typename... Args>
            weak<ActorType> SpawnActor(Args... args_);

            void Render(sf::RenderWindow& window_);

            sf::Vector2u GetWindowSize() const;

            void CleanCycle();
            void AddStage(const shared<GameStage>& newStage_);

        private:

            virtual void BeginPlay();
            virtual void Tick(float deltaTime_);
            
            Application* mOwningApp;
            bool mBegunPlay{false};

            List<shared<Actor>> mActors;
            List<shared<Actor>> mPendingActors;
            List<shared<GameStage>> mGameStages;
            int mCurrentStageIndex;
            virtual void InitGameStages();
            virtual void AllGameStageFinished();
            void NextGameStage();
    };

    template<typename ActorType, typename... Args>
    inline weak<ActorType> World::SpawnActor(Args... args_)
    {
        shared<ActorType> newActor{new ActorType(this, args_...)};
        mPendingActors.push_back(newActor);
        return newActor;
    }

}