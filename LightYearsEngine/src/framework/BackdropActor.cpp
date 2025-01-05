#include "framework/BackdropActor.h"

#include <sys/types.h>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "framework/World.h"

namespace ly
{
    BackdropActor::BackdropActor(World* owningWorld_, const std::string& texturePath_, const sf::Vector2f& velocity_)
        : Actor{owningWorld_, texturePath_}
        , mMovingVelocity(velocity_)
        , mLeftShift{0}
        , mTopShift{0}
    {
        sf::Vector2u _windowSize = owningWorld_->GetWindowSize();
        GetSprite().setOrigin(0.f, 0.f);
        GetSprite().setTextureRect(sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{(int)_windowSize.x, (int)_windowSize.y}});
        SetTextureRepeated(true);
    }

    void BackdropActor::Tick(float deltaTime_)
    {
        Actor::Tick(deltaTime_);

        mLeftShift += deltaTime_ * mMovingVelocity.x;
        mTopShift += deltaTime_ * mMovingVelocity.y;

        sf::IntRect _currentRect = GetSprite().getTextureRect();
        _currentRect.left = mLeftShift;
        _currentRect.top = mTopShift;

        GetSprite().setTextureRect(_currentRect);
    }
}  // namespace ly
