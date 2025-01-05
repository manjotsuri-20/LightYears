#include "framework/MathUtility.h"

#include <math.h>

#include <random>

#include "SFML/Config.hpp"
#include "framework/MathUtility.h"

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
        return degrees_ * (PI / 180.f);
    }

    float RadiansToDegrees(float radians_)
    {
        return radians_ * (180.f / PI);
    }

    float LerpFloat(float a_, float b_, float alpha_)
    {
        if (alpha_ > 1) alpha_ = 1;
        if (alpha_ < 0) alpha_ = 0;

        return a_ + (b_ - a_) * alpha_;
    }

    sf::Vector2f LerpVector(const sf::Vector2f& a_, const sf::Vector2f& b_, float alpha_)
    {
        float _lerpX = LerpFloat(a_.x, b_.x, alpha_);
        float _lerpY = LerpFloat(a_.y, b_.y, alpha_);

        return sf::Vector2f{_lerpX, _lerpY};
    }

    sf::Color LerpColor(const sf::Color& a_, const sf::Color& b_, float alpha_)
    {
        sf::Uint8 _lerpR = LerpFloat(a_.r, b_.r, alpha_);
        sf::Uint8 _lerpG = LerpFloat(a_.g, b_.g, alpha_);
        sf::Uint8 _lerpB = LerpFloat(a_.b, b_.b, alpha_);
        sf::Uint8 _lerpA = LerpFloat(a_.a, b_.a, alpha_);

        return sf::Color{_lerpR, _lerpG, _lerpB, _lerpA};
    }

    float RandomRange(float min_, float max_)
    {
        std::random_device rd_;
        std::mt19937 gen_(rd_());

        std::uniform_real_distribution<float> distribution_{min_, max_};
        return distribution_(gen_);
    }

    sf::Vector2f RandomUnitVector()
    {
        float randomX_ = RandomRange(-1, 1);
        float randomY_ = RandomRange(-1, 1);

        sf::Vector2f randVec_{randomX_, randomY_};
        Normalize(randVec_);

        return randVec_;
    }
}  // namespace ly
