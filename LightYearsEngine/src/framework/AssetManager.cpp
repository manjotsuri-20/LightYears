#include "framework/AssetManager.h"

namespace ly
{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get()
    {
        if(!assetManager)
        {
            assetManager = std::move(unique<AssetManager>{new AssetManager});
        }
        return *assetManager;
    }

    AssetManager::AssetManager() : mRootDirectory{}
    {

    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string& path_)
    {
        return LoadAsset(path_, mLoadedTextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string& path_)
    {
        return LoadAsset(path_, mLoadedFontMap);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
    }

    void AssetManager::SetAssetRootDirectory(const std::string &directory_)
    {
        mRootDirectory = directory_;
    }
}