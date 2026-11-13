#include "display.h"
#include "tile.h"
#include "entity.h"
#include "raylib.h"
#include <string>
#include <algorithm>

using namespace std;

Display::Display()
{
    messageCount = 0;
    visualX = 0;
    visualY = 0;
    targetX = 0;
    targetY = 0;
    moveSpeed = 10.0f;

    grassTex = LoadTexture("assets/grass.png");
    flowerTex = LoadTexture("assets/sunflower_grass.png");
    playerTex = LoadTexture("assets/player.png");
    robotTex = LoadTexture("assets/robot.png");
    stewTex = LoadTexture("assets/stew.png");
    boneTileTex = LoadTexture("assets/bone_tile.png");
    robotTileTex = LoadTexture("assets/robot_tile.png");
    machineTileTex = LoadTexture("assets/machine_tile.png");
    dogTex = LoadTexture("assets/dog.png");
    machineTex = LoadTexture("assets/machine.png");
    screwTex = LoadTexture("assets/screw.png");
}

Display::~Display()
{
    UnloadTexture(grassTex);
    UnloadTexture(flowerTex);
    UnloadTexture(playerTex);
    UnloadTexture(robotTex);
    UnloadTexture(stewTex);
    UnloadTexture(boneTileTex);
    UnloadTexture(robotTileTex);
    UnloadTexture(machineTileTex);
    UnloadTexture(dogTex);
    UnloadTexture(machineTex);
    UnloadTexture(screwTex);
}

void Display::addMessage(string msg)
{
    if (messageCount < MAX_MESSAGES)
    {
        messages[messageCount++] = msg;
    }
    else
    {
        for (int i = 0; i < MAX_MESSAGES - 1; i++)
            messages[i] = messages[i + 1];
        messages[MAX_MESSAGES - 1] = msg;
    }
}

string Display::getLastMessage() const
{
    if (messageCount == 0)
        return "";
    return messages[messageCount - 1];
}

void Display::clearLastMessage()
{
    if (messageCount > 0)
        messageCount--;
}

void Display::drawHealthBar(int health)
{
    int barX = 580, barY = 20;
    int barW = 200, barH = 20;
    DrawRectangle(barX, barY, barW, barH, DARKGRAY);
    int filled = (health * barW) / 100;
    Color col = GREEN;
    if (health <= 60)
        col = YELLOW;
    if (health <= 30)
        col = RED;
    DrawRectangle(barX, barY, filled, barH, col);
    DrawText(("HP: " + to_string(health)).c_str(), barX, barY + 25, 16, WHITE);
}

void Display::drawInfoPanel(Player &player)
{
    DrawRectangle(570, 0, 230, 560, {15, 15, 25, 255});
    DrawText("PROTOCOL: ECHO", 578, 5, 14, {100, 255, 100, 255});
    drawHealthBar(player.getHealth());
    DrawText("STATUS:", 580, 70, 16, WHITE);
    if (player.isPoisoned())
        DrawText("POISONED", 580, 90, 16, RED);
    else
        DrawText("Normal", 580, 90, 16, GREEN);
    DrawText("HOLDING:", 580, 120, 16, WHITE);
    string item = "Nothing";
    if (player.hasScrewItem())
        item = "Screw";
    else if (player.hasMapItem())
        item = "Map";
    else if (player.hasBoneItem())
        item = "Bone";
    DrawText(item.c_str(), 580, 140, 16, YELLOW);
    DrawText("WASD: Move", 580, 500, 14, DARKGRAY);
    DrawText("Q: Quit", 580, 518, 14, DARKGRAY);
    DrawText("E: Interact", 580, 536, 14, DARKGRAY);
}

void Display::drawMap(Map &map, Player &player)
{
    const int VIEW = 7;
    const int HALF = VIEW / 2;
    const int WORLD = 16;

    int pGR = map.toGlobalRow(player.getBlockRow(), player.getRow());
    int pGC = map.toGlobalCol(player.getBlockCol(), player.getCol());

    targetX = pGC * TILE_SIZE;
    targetY = pGR * TILE_SIZE;
    visualX += (targetX - visualX) * 0.35f;
    visualY += (targetY - visualY) * 0.35f;

    int camOffX = (int)visualX - (HALF * TILE_SIZE);
    int camOffY = (int)visualY - (HALF * TILE_SIZE);

    int startR = max(0, pGR - HALF - 1);
    int startC = max(0, pGC - HALF - 1);
    int endR = min(WORLD - 1, pGR + HALF + 1);
    int endC = min(WORLD - 1, pGC + HALF + 1);

    // PASS 1: tiles and entities
    for (int gr = startR; gr <= endR; gr++)
    {
        for (int gc = startC; gc <= endC; gc++)
        {
            Tile &tile = map.getTileGlobal(gr, gc);
            int screenX = gc * TILE_SIZE - camOffX;
            int screenY = gr * TILE_SIZE - camOffY;

            if (screenX < -TILE_SIZE || screenX > 560 ||
                screenY < -TILE_SIZE || screenY > 560)
                continue;

            // Floor
            if (tile.isWalkable())
            {
                Texture2D *tex = nullptr;
                if (gr >= 0 && gr <= 3 && gc >= 12 && gc <= 15)
                    tex = &boneTileTex;
                else if (gr >= 12 && gr <= 15 && gc >= 12 && gc <= 15)
                    tex = &robotTileTex;
                else if (gr >= 4 && gr <= 7 && gc >= 8 && gc <= 11)
                    tex = &machineTileTex;
                else
                    tex = ((gr + gc) % 3 == 0) ? &flowerTex : &grassTex;
                DrawTexturePro(*tex,
                               {0, 0, (float)tex->width, (float)tex->height},
                               {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                               {0, 0}, 0.0f, WHITE);
            }
            // Wall
            else
            {
                DrawRectangle(screenX, screenY, TILE_SIZE, TILE_SIZE, {60, 60, 60, 255});
                DrawRectangle(screenX, screenY, TILE_SIZE, 3, {40, 40, 40, 255});
                DrawRectangle(screenX, screenY + TILE_SIZE / 2, TILE_SIZE, 3, {40, 40, 40, 255});
                DrawRectangle(screenX + TILE_SIZE / 2, screenY, 3, TILE_SIZE / 2, {40, 40, 40, 255});
                DrawRectangle(screenX + TILE_SIZE / 4, screenY + TILE_SIZE / 2, 3, TILE_SIZE / 2, {40, 40, 40, 255});
                DrawLine(screenX + 15, screenY + 5, screenX + 20, screenY + 25, {30, 30, 30, 255});
            }

            DrawRectangleLines(screenX, screenY, TILE_SIZE, TILE_SIZE, {20, 50, 20, 50});

            if (gr == pGR && gc == pGC)
                continue;

            // Occupants
            if (tile.getOccupant() != nullptr)
            {
                Entity *e = tile.getOccupant();
                int c = e->getColor();
                if (e->getSymbol() == 'R')
                {
                    Color tint = (c == 12) ? RED : WHITE;
                    DrawTexturePro(robotTex,
                                   {0, 0, (float)robotTex.width, (float)robotTex.height},
                                   {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                                   {0, 0}, 0.0f, tint);
                }
                else if (e->getSymbol() == 'D')
                {
                    DrawTexturePro(dogTex,
                                   {0, 0, (float)dogTex.width, (float)dogTex.height},
                                   {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                                   {0, 0}, 0.0f, WHITE);
                }
                else
                {
                    Color col = WHITE;
                    if (c == 9)
                        col = BLUE;
                    if (c == 12)
                        col = RED;
                    if (c == 14)
                        col = YELLOW;
                    DrawCircle(screenX + 35, screenY + 35, 18, col);
                    string sym(1, e->getSymbol());
                    DrawText(sym.c_str(), screenX + 28, screenY + 26, 22, BLACK);
                }
            }
            // Items
            else if (tile.getObject() != nullptr)
            {
                Entity *obj = tile.getObject();
                char sym = obj->getSymbol();
                if (sym == 'S')
                {
                    DrawTexturePro(stewTex,
                                   {0, 0, (float)stewTex.width, (float)stewTex.height},
                                   {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                                   {0, 0}, 0.0f, WHITE);
                }
                else if (sym == 'B')
                {
                    DrawRectangle(screenX + 25, screenY + 35, 22, 6, {230, 220, 200, 255});
                    DrawCircle(screenX + 25, screenY + 38, 8, {230, 220, 200, 255});
                    DrawCircle(screenX + 47, screenY + 38, 8, {230, 220, 200, 255});
                    DrawText("Bone", screenX + 18, screenY + 52, 12, {230, 220, 200, 255});
                }
                else if (sym == 'V')
                {
                    DrawTexturePro(screwTex,
                                   {0, 0, (float)screwTex.width, (float)screwTex.height},
                                   {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                                   {0, 0}, 0.0f, WHITE);
                }
                else if (sym == 'T')
                {
                    DrawTexturePro(machineTex,
                                   {0, 0, (float)machineTex.width, (float)machineTex.height},
                                   {(float)screenX, (float)screenY, (float)TILE_SIZE, (float)TILE_SIZE},
                                   {0, 0}, 0.0f, WHITE);
                }
                else
                {
                    DrawCircle(screenX + 35, screenY + 35, 10, GREEN);
                    string s(1, sym);
                    DrawText(s.c_str(), screenX + 28, screenY + 26, 22, BLACK);
                }
            }
        }
    }

    // PASS 2: player always on top
    int cx = 560 / 2 - TILE_SIZE / 2;
    int cy = 560 / 2 - TILE_SIZE / 2;
    DrawTexturePro(playerTex,
                   {0, 0, (float)playerTex.width, (float)playerTex.height},
                   {(float)cx, (float)cy, (float)TILE_SIZE, (float)TILE_SIZE},
                   {0, 0}, 0.0f, WHITE);
}

void Display::drawMessagePanel()
{
    DrawRectangle(0, 565, 570, 155, {10, 10, 20, 255});
    DrawText("LOG:", 10, 568, 14, {100, 255, 100, 255});
    for (int i = 0; i < messageCount; i++)
    {
        string line = "> " + messages[i];
        DrawText(line.c_str(), 10, 585 + i * 22, 14, {180, 255, 180, 255});
    }
}

void Display::render(Map &map, Player &player)
{
    drawMap(map, player);
    drawInfoPanel(player);
    drawMessagePanel();
}

void Display::drawMachinePuzzle(int step, const string &message)
{
    DrawRectangle(50, 50, 500, 460, {10, 10, 20, 255});
    DrawRectangleLines(50, 50, 500, 460, {0, 180, 0, 255});
    DrawText("--- MACHINE TERMINAL ---", 100, 80, 22, {0, 255, 0, 255});
    DrawLine(50, 112, 550, 112, {0, 100, 0, 255});

    if (step == 0)
    {
        DrawText("The machine has three controls.", 80, 135, 16, WHITE);
        DrawText("Press 1 - Pull Lever", 80, 190, 18, {200, 200, 0, 255});
        DrawText("Press 2 - Press Red Button", 80, 225, 18, {200, 0, 0, 255});
        DrawText("Press 3 - Turn Dial", 80, 260, 18, {0, 200, 200, 255});
    }
    else
    {
        DrawText("The dial clicks. One action remains.", 80, 135, 16, WHITE);
        DrawText("Press 1 - Pull Lever", 80, 190, 18, {200, 200, 0, 255});
        DrawText("Press 2 - Press Red Button", 80, 225, 18, {200, 0, 0, 255});
    }

    DrawText("Press ESC to step back.", 80, 440, 14, DARKGRAY);

    if (!message.empty())
        DrawText(message.c_str(), 80, 360, 16, {0, 200, 100, 255});
}

void Display::drawFinalPuzzle(const string &inputBuffer)
{
    DrawRectangle(50, 50, 500, 460, {10, 10, 20, 255});
    DrawRectangleLines(50, 50, 500, 460, {0, 180, 0, 255});
    DrawText("--- DECODING TERMINAL ---", 100, 80, 22, {0, 255, 0, 255});
    DrawLine(50, 112, 550, 112, {0, 100, 0, 255});

    DrawText("[RED]    01010011", 100, 145, 20, RED);
    DrawText("[GREEN]  65", 100, 180, 20, GREEN);
    DrawText("[BLUE]   126", 100, 215, 20, BLUE);
    DrawText("[YELLOW] 01000101", 100, 250, 20, YELLOW);

    DrawText("Decode each to a letter. Enter the word:", 100, 310, 15, GRAY);
    DrawText("Enter decoded word:", 100, 350, 18, WHITE);

    string disp = inputBuffer + "_";
    DrawText(disp.c_str(), 100, 385, 26, {0, 255, 100, 255});

    DrawText("Press ENTER to submit, BACKSPACE to delete.", 80, 440, 13, DARKGRAY);
}

void Display::showDeath(const string &reason)
{
    ClearBackground({10, 10, 10, 255});
    DrawText("GAME OVER", 220, 180, 60, RED);
    DrawLine(100, 255, 700, 255, {80, 0, 0, 255});
    DrawText(reason.c_str(), 100, 280, 18, {180, 60, 60, 255});
    DrawText("Press any key...", 280, 400, 20, GRAY);
}

void Display::showWin(const string &reason)
{
    ClearBackground({10, 10, 10, 255});
    DrawText("YOU ESCAPED", 200, 180, 48, GREEN);
    DrawLine(100, 245, 700, 245, {0, 80, 0, 255});
    DrawText(reason.c_str(), 100, 270, 18, {100, 220, 100, 255});
    DrawText("The system behind the robot remains unknown.", 100, 330, 16, DARKGRAY);
    DrawText("You were manipulated. Something bigger exists.", 100, 355, 16, DARKGRAY);
    DrawText("Press any key...", 280, 430, 20, GRAY);
}
