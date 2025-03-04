#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly
{
    class AssetManager
    {
        public:
        static AssetManager& Get();

        shared<sf::Texture>     LoadTexture(const std::string& path_);
        shared<sf::Font>        LoadFont(const std::string& path_);
        shared<sf::SoundBuffer> LoadSoundBuffer(const std::string& path_);
        unique<sf::Music>       LoadMusic(const std::string& path_);

        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory_);

        protected:
        AssetManager();

        private:
        template <typename T>
        shared<T> LoadAsset(const std::string& path_, Dictionary<std::string, shared<T>>& container_);
        template <typename T>
        void                        CleanUniqueRef(Dictionary<std::string, shared<T>>& container_);
        static unique<AssetManager> assetManager;
        std::string                 mRootDirectory;

        Dictionary<std::string, shared<sf::Texture>>     mLoadedTextureMap;
        Dictionary<std::string, shared<sf::Font>>        mLoadedFontMap;
        Dictionary<std::string, shared<sf::SoundBuffer>> mLoadedSoundBufferMap;
    };

    template <typename T>
    inline shared<T> AssetManager::LoadAsset(const std::string& path_, Dictionary<std::string, shared<T>>& container_)
    {
        auto _found = container_.find(path_);
        if (_found != container_.end())
        {
            return _found->second;
        }
        shared<T> _newAsset{new T};
        if (_newAsset->loadFromFile(mRootDirectory + path_))
        {
            LOG("Asset Loaded %s", path_.c_str());
            container_.insert({path_, _newAsset});
            return _newAsset;
        }
        return shared<T>{nullptr};
    }

    template <typename T>
    inline void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& container_)
    {
        for (auto iter = container_.begin(); iter != container_.end();)
        {
            if (iter->second.unique())
            {
                LOG("cleaning asset: %s", iter->first.c_str());
                iter = container_.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}  // namespace ly
