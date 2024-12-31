#include "Enemy/ChaosStage.h"

#include "Enemy/Hexagon.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/UFO.h"
#include "Enemy/Vanguard.h"
#include "SFML/System/Vector2.hpp"
#include "framework/MathUtility.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
    ChaosStage::ChaosStage(World* world_)
        : GameStage{world_}
        , mSpawnInterval{4.f}
        , mMinSpawnInterval{0.8f}
        , mSpawnIntervalDecrement{0.5f}
        , mSpawnIntervalDecrementInterval{5.f}
        , mStageDuration{60.f}
    {
    }

    void ChaosStage::StartStage()
    {
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
        mDifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrementInterval, true);
        TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
    }

    void ChaosStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mDifficultTimerHandle);
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
    }

    void ChaosStage::IncreaseDifficulty()
    {
        mSpawnInterval -= mSpawnIntervalDecrementInterval;
        if (mSpawnInterval < mMinSpawnInterval)
        {
            mSpawnInterval = mMinSpawnInterval;
        }
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
    {
        auto _windowSize = GetWorld()->GetWindowSize();
        float _spawnX = RandomRange(100.f, _windowSize.x - 100.f);
        float _spawnY = -100.f;

        return sf::Vector2f{_spawnX, _spawnY};
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
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

    void ChaosStage::SpawnVanguard()
    {
        weak<Vanguard> _newVanguard = GetWorld()->SpawnActor<Vanguard>();
        _newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        _newVanguard.lock()->SetActorRotation(90.f);
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
    }

    void ChaosStage::SpawnTwinBlade()
    {
        weak<TwinBlade> _newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        _newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
    }

    void ChaosStage::SpawnHexagon()
    {
        weak<Hexagon> _newHexagon = GetWorld()->SpawnActor<Hexagon>();
        _newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
    }

    void ChaosStage::SpawnUFO()
    {
        sf::Vector2f _spawnLocation = GetRandomSpawnLocationSide();

        auto _windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f _centre = sf::Vector2f{_windowSize.x / 2.f, _windowSize.y / 2.f};
        sf::Vector2f _dirToCentre = _centre - _spawnLocation;
        Normalize(_dirToCentre);

        weak<UFO> _newUFO = GetWorld()->SpawnActor<UFO>(_dirToCentre * 200.f);
        _newUFO.lock()->SetActorLocation(_spawnLocation);

        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
    }

    void ChaosStage::StageDurationReached()
    {
        StageFinished();
    }
}  // namespace ly
