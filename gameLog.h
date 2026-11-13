#ifndef GAMELOG_H
#define GAMELOG_H

#include <fstream>
#include <string>
#include "player.h"

class GameLog
{
private:
    std::ofstream file;

public:
    GameLog()
    {
        file.open("game_log.txt", std::ios::out | std::ios::trunc);
        file << "=== PROTOCOL: ECHO — SESSION LOG ===\n\n";
    }

    ~GameLog()
    {
        if (file.is_open())
            file.close();
    }

    void logEvent(const std::string &event)
    {
        if (file.is_open())
            file << "[EVENT] " << event << "\n";
    }

    void logPlayerState(const Player &player)
    {
        if (file.is_open())
            file << "[STATE] " << player << "\n";
    }

    void logResult(const std::string &result, const Player &player)
    {
        if (file.is_open())
        {
            file << "\n=== RESULT ===\n";
            file << result << "\n";
            file << "Final state — " << player << "\n";
        }
    }
};

#endif
