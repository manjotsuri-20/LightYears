#include "framework/World.h"

#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly
{
    World::World(Application* owningApp)
        : mOwningApp(owningApp)
        , mBegunPlay(false)
        , mActors{}
        , mPendingActors{}
        , mGameStages{}
        , mCurrentStage{mGameStages.end()}
        , mHUD{nullptr}
    {
    }

    void World::BeginPlayInternal()
    {
        if (!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(float deltaTime_)
    {
        for (shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();
        for (auto iter = mActors.begin(); iter != mActors.end(); iter++)
        {
            iter->get()->TickInternal(deltaTime_);
        }

        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->TickStage(deltaTime_);
        }

        Tick(deltaTime_);

        if (mHUD)
        {
            if (!mHUD->HasInit())
            {
                mHUD->NativeInit(mOwningApp->GetWindow());
            }
            mHUD->Tick(deltaTime_);
        }
    }

    World::~World()
    {
        LOG("World Destroyed");
    }

    void World::RenderHUD(sf::RenderWindow& window_)
    {
        if (mHUD)
        {
            mHUD->Draw(window_);
        }
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
        LOG("All stages finished");
    }

    void World::NextGameStage()
    {
        mCurrentStage = mGameStages.erase(mCurrentStage);
        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStageFinished();
        }
    }

    void World::StartStages()
    {
        mCurrentStage = mGameStages.begin();
        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
    }

    void World::Render(sf::RenderWindow& window_)
    {
        for (auto& actor : mActors)
        {
            actor->Render(window_);
        }
        RenderHUD(window_);
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage>& newStage_)
    {
        mGameStages.push_back(newStage_);
    }

    bool World::DispatchEvent(const sf::Event& event_)
    {
        if (mHUD)
        {
            return mHUD->HandleEvent(event_);
        }
        return false;
    }
}  // namespace ly
