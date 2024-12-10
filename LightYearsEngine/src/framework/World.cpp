#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
    World::World(Application* owningApp)
        : mOwningApp(owningApp),
        mBegunPlay(false),
        mActors{},
        mPendingActors{},
        mCurrentStageIndex{-1},
        mGameStages{}
    {
    }

    void World::BeginPlayInternal()
    {
        if(!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
            InitGameStages();
            NextGameStage();
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
        
        if(mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
        {
            mGameStages[mCurrentStageIndex]->TickStage(deltaTime_);
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

    void World::InitGameStages()
    {
    }

    void World::AllGameStageFinished()
    {
    }

    void World::NextGameStage()
    {
        ++mCurrentStageIndex;
        if(mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
        {
            mGameStages[mCurrentStageIndex]->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
            mGameStages[mCurrentStageIndex]->StartStage();
        }
        else
        {
            AllGameStageFinished();
        }
    }

    void World::Render(sf::RenderWindow &window_)
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

        for(auto iter = mGameStages.begin(); iter != mGameStages.end();)
        {
            if(iter->get()->IsStageFinished())
            {
                iter = mGameStages.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage> &newStage_)
    {
        mGameStages.push_back(newStage_);
    }
}
