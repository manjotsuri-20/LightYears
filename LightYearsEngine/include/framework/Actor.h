#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/AssetManager.h"

namespace ly
{
    class World;
    class Actor : public Object
    {
        public:

            Actor(World* owningWorld, const std::string& texturePath_ = "");

            void BeginPlayInternal();

            void TickInternal(float deltaTime_);

            virtual void BeginPlay();

            virtual void Tick(float deltaTime_);

            void SetTexture(const std::string& texturePath_);

            void Render(sf::RenderWindow& window_);

            void SetActorLocation(const sf::Vector2f& newLoc_);

            void SetActorRotation(float newRot_);

            void AddActorLocationOffset(const sf::Vector2f& offsetAmt_);

            void AddActorRotationOffset(float offsetAmt_);

            sf::Vector2f GetActorLocation() const;

            float GetActorRotation() const;

            sf::Vector2f GetActorForwardDirection() const;

            sf::Vector2f GetActorRightDirection() const;

            sf::Vector2u GetWindowSize() const;

            sf::FloatRect GetActorGlobalBounds() const;

            World* GetWorld() const;

            bool IsActorOutOfWindowBounds() const;

            virtual ~Actor();

        private:

            void CentrePivot();

            World* mOwningWorld;
            bool mHasBeganPlay{false};

            sf::Sprite mSprite;
            shared<sf::Texture> mTexture;
    };
}