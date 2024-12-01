#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "framework/Core.h"

namespace ly
{
    sf::Vector2f RotationToVector(float rotation_);
    float DegreesToRadians(float degrees_);
    float RadiansToDegrees(float radians_);    

    template<typename T>
    float GetVectorLength(sf::Vector2<T>& vector_)
    {
        return std::sqrt(vector_.x * vector_.x + vector_.y * vector_.y);
    }

    template<typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale_, float amt_)
    {
        vectorToScale_.x *= amt_;
        vectorToScale_.y *= amt_;
        return vectorToScale_;
    }

    template<typename T>
    void Normalize(sf::Vector2<T>& vector_)
    {
        float _vectorLength = GetVectorLength<T>(vector_);
        if(_vectorLength == 0.f)
        {
            // LOG("Vector length: %f", _vectorLength);
            return;
        }
        ScaleVector(vector_, 1.0/_vectorLength);
    }
}