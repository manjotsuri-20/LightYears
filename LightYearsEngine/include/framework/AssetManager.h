#pragma once
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly
{
    class AssetManager
    {
        public:
            static AssetManager& Get();
            shared<sf::Texture> LoadTexture(const std::string& path_);
            void CleanCycle();
            void SetAssetRootDirectory(const std::string& directory_);

        protected:
            AssetManager();

        private:
            static unique<AssetManager> assetManager;
            std::string mRootDirectory;
            Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
    };
}