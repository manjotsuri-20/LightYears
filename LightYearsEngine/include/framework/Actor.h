#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/AssetManager.h"

class b2Body;
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

            const World* GetWorld() const;

            World* GetWorld() { return mOwningWorld; }

            bool IsActorOutOfWindowBounds() const;

            void SetEnablePhysics(bool enable_);

            void UpdatePhysicsTransform();

            virtual void OnActorBeginOverlap(Actor* other_);

            virtual void OnActorEndOverlap(Actor* other_);

            virtual void Destroy() override;

            static uint8 GetNeutralTeamID() { return neutralTeamID; }

            uint8 GetTeamID() const { return mTeamID; }

            bool IsOtherHostile(Actor* other_) const;

            void SetTeamID(uint8 teamId_) { mTeamID = teamId_; }

            virtual void ApplyDamage(float amt_);

            sf::Sprite& GetSprite() { return mSprite; }

            const sf::Sprite& GetSprite() const { return mSprite; }

            virtual ~Actor();

        private:

            void InitializePhysics();
            void UnInitializedPhysics();
            void CentrePivot();

            World* mOwningWorld;
            bool mHasBeganPlay{false};

            sf::Sprite mSprite;
            shared<sf::Texture> mTexture;
            
            b2Body* mPhysicsBody;
            bool mPhysicsEnable;

            uint8 mTeamID;

            const static uint8 neutralTeamID = 255;
    };
}