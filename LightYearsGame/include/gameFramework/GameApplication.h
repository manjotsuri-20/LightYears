#include "framework/Application.h"
#include "framework/Core.h"
#include "spaceship/Spaceship.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    class Actor;
    class Spaceship;
    class PlayerSpaceship;
    class GameApplication : public Application
    {
        public:

            GameApplication();

            ~GameApplication();

            virtual void Tick(float deltaTime_) override;

        private:

            float counter;
            weak<PlayerSpaceship> testPlayerSpaceship;
    };
}