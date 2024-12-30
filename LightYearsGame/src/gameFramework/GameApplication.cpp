#include "gameFramework/GameApplication.h"

#include "Level/MainMenuLevel.h"
#include "config.h"
#include "framework/AssetManager.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application{600, 900, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
    }

    GameApplication::~GameApplication()
    {
        LOG("Game Application destroyed");
    }
}  // namespace ly
