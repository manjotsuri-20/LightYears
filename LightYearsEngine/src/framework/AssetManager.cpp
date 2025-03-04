#include "framework/AssetManager.h"

#include <filesystem>

#include "SFML/Audio/Music.hpp"
#include "framework/Core.h"

namespace ly
{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get()
    {
        if (!assetManager)
        {
            assetManager = std::move(unique<AssetManager>{new AssetManager});
        }
        return *assetManager;
    }

    AssetManager::AssetManager()
        : mRootDirectory{}
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

    shared<sf::SoundBuffer> AssetManager::LoadSoundBuffer(const std::string& path_)
    {
        return LoadAsset(path_, mLoadedSoundBufferMap);
    }

    unique<sf::Music> AssetManager::LoadMusic(const std::string& path_)
    {
        unique<sf::Music> _music = makeUnique<sf::Music>();
        _music->openFromFile(mRootDirectory + path_);
        return std::move(_music);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
        CleanUniqueRef(mLoadedSoundBufferMap);
    }

    void AssetManager::SetAssetRootDirectory(const std::string& directory_)
    {
        mRootDirectory = directory_;
    }
}  // namespace ly
