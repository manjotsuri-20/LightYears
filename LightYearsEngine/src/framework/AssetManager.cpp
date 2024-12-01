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
        auto _found = mLoadedTextureMap.find(path_);
        if(_found != mLoadedTextureMap.end())
        {
            return _found->second;
        }
        shared<sf::Texture> _newTexture{new sf::Texture};
        if(_newTexture->loadFromFile(mRootDirectory + path_))
        {
            mLoadedTextureMap.insert({path_, _newTexture});
            return _newTexture;
        }
        return shared<sf::Texture>{nullptr};
    }

    void AssetManager::CleanCycle()
    {
        for(auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
        {
            if(iter->second.unique())
            {
                LOG("cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    void AssetManager::SetAssetRootDirectory(const std::string &directory_)
    {
        mRootDirectory = directory_;
    }
}