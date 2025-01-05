#pragma once
#include <string>

std::string GetResourceDir()
{
    #ifdef NDEBUG //release build
        return "assets/";
    #else
        return "/home/manjot.suri/Game/LightYears/LightYearsGame/assets/";
    #endif
}
