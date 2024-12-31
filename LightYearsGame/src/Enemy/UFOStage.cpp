#include "Enemy/UFOStage.h"

#include "Enemy/UFO.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    UFOStage::UFOStage(World* owningWorld_)
        : GameStage{owningWorld_}
        , mSpawnInterval{4.f}
        , mSpawnAmt{10}
        , mCurrentSpawnAmt{0}
        , mUFOSpeed{200.f}
        , mSpawnTimer{}
    {
    }

    void UFOStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
    }

    void UFOStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    sf::Vector2f UFOStage::GetRandomSpawnLoc() const
    {
        auto _windowSize = GetWorld()->GetWindowSize();
        float _spawnLeft = RandomRange(-1, 1);
        float _spawnLocX = 0;
        if (_spawnLeft < 0)
        {
            _spawnLocX = _windowSize.x + 100.f;
        }
        else
        {
            _spawnLocX = -100.f;
        }

        float _spawnLocY = RandomRange(0, _windowSize.y);

        return sf::Vector2f{_spawnLocX, _spawnLocY};
    }

    void UFOStage::SpawnUFO()
    {
        sf::Vector2f _spawnLoc = GetRandomSpawnLoc();
        auto _windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f _centre{_windowSize.x / 2.f, _windowSize.y / 2.f};
        sf::Vector2f _spawnLocToCentre{_centre.x - _spawnLoc.x, _centre.y - _spawnLoc.y};
        Normalize(_spawnLocToCentre);

        sf::Vector2f _spawnVelocity = _spawnLocToCentre * mUFOSpeed;

        weak<UFO> _newUFO = GetWorld()->SpawnActor<UFO>(_spawnVelocity);
        _newUFO.lock()->SetActorLocation(_spawnLoc);

        if (++mCurrentSpawnAmt == mSpawnAmt)
        {
            FinishStage();
        }
    }
}  // namespace ly
