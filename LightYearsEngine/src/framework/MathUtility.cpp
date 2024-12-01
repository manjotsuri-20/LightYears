#include "framework/MathUtility.h"
#include "framework/MathUtility.h"
#include <math.h>

namespace ly
{
    const float PI = 3.141592653689;

    sf::Vector2f RotationToVector(float rotation_)
    {
        float _radians = DegreesToRadians(rotation_);

        return sf::Vector2f(std::cos(_radians), std::sin(_radians));
    }

    float DegreesToRadians(float degrees_)
    {
        return degrees_ * (PI/180.f);
    }

    float RadiansToDegrees(float radians_)
    {
        return radians_ * (180.f/PI);
    }
}