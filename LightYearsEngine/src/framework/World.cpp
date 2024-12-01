#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace ly
{
    World::World(Application* owningApp)
        : mOwningApp(owningApp),
        mBegunPlay(false),
        mActors{},
        mPendingActors{}
    {

    }

    void World::BeginPlayInternal()
    {
        if(!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime_)
    {
        for(shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();
        for(auto iter = mActors.begin(); iter != mActors.end(); iter++)
        {
            iter->get()->TickInternal(deltaTime_);
        }
        Tick(deltaTime_);
    }

    World::~World()
    {
        LOG("World Destroyed");
    }

    void World::BeginPlay()
    {
        // LOG("Begin Play");
    }

    void World::Tick(float deltaTime_)
    {
        // LOG("Tick at frame rate %f", 1.f / deltaTime_);
    }

    void World::Render(sf::RenderWindow& window_)
    {
        for(auto& actor : mActors)
        {
            actor->Render(window_);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }
    
    void World::CleanCycle()
    {
        for(auto iter = mActors.begin(); iter != mActors.end(); )
        {
            if(iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

