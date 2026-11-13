#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"
#include <string>
#include "map.h"
#include "player.h"

class Display {
private:
    static const int MAX_MESSAGES = 5;
    static const int TILE_SIZE = 80;

    std::string messages[MAX_MESSAGES];
    int messageCount;

    float visualX;
    float visualY;
    float targetX;
    float targetY;
    float moveSpeed;

    Texture2D grassTex;
    Texture2D flowerTex;
    Texture2D playerTex;
    Texture2D robotTex;
    Texture2D stewTex;
    Texture2D boneTileTex;
    Texture2D robotTileTex;
    Texture2D machineTileTex;
    Texture2D dogTex;
    Texture2D machineTex;
    Texture2D screwTex;

    void drawMap(Map& map, Player& player);
    void drawInfoPanel(Player& player);
    void drawMessagePanel();
    void drawHealthBar(int health);

public:
    Display();
    ~Display();
    void addMessage(std::string msg);
    std::string getLastMessage() const;
    void clearLastMessage();
    void render(Map& map, Player& player);
    void showDeath(const std::string&  reason);
    void showWin(const std::string& reason);
    void drawMachinePuzzle(int step, const std::string& message);
    void drawFinalPuzzle(const std::string& inputBuffer);
};

#endif
