#include "player/PlayerManager.h"
#include "player/Player.h"

namespace ly
{
    unique<PlayerManager> PlayerManager::mPlayerManager{nullptr};

    PlayerManager::PlayerManager()
    {}

    Player& PlayerManager::CreateNewPlayer()
    {
        mPlayers.emplace(mPlayers.begin(), Player());
        return mPlayers.back();
    }

    Player* PlayerManager::GetPlayer(int playerIndex_)
    {
        if(playerIndex_ >= 0 && playerIndex_ <= mPlayers.size())
        {
            return &mPlayers[playerIndex_];
        }
        return nullptr;
    }

    const Player* PlayerManager::GetPlayer(int playerIndex_) const
    {
        if(playerIndex_ >= 0 && playerIndex_ <= mPlayers.size())
        {
            return &mPlayers[playerIndex_];
        }
        return nullptr;
    }

    PlayerManager& PlayerManager::Get()
    {
        if(!mPlayerManager)
        {
            mPlayerManager = std::move(unique<PlayerManager>{new PlayerManager});
        }
        return *mPlayerManager;
    }
} // namespace ly

