#include <iostream>
#include "map.h"
#include "entity.h"

using namespace std;

Map::Map()
{
    generateMap();
}

Tile &Map::getTile(int br, int bc, int r, int c)
{
    return world[br][bc][r][c];
}

Tile &Map::getTileGlobal(int gr, int gc)
{
    int br, bc, r, c;
    Map::toLocal(gr, gc, br, bc, r, c);
    return world[br][bc][r][c];
}

void Map::generateMap()
{
    // Step 1: fill everything as empty first
    for (int br = 0; br < WORLD_SIZE; br++)
        for (int bc = 0; bc < WORLD_SIZE; bc++)
            for (int r = 0; r < BLOCK_SIZE; r++)
                for (int c = 0; c < BLOCK_SIZE; c++)
                    world[br][bc][r][c].setEmpty();

    // Step 2: helper — walls the border of a block, doorway at given side
    // We'll just write it manually per block for clarity

    // --- Block (0,3): House with bone inside ---
    // Border walls
    world[0][3][0][0].setWall();
    world[0][3][0][1].setWall();
    world[0][3][0][2].setWall();
    world[0][3][0][3].setWall();
    world[0][3][1][0].setWall();
    world[0][3][1][3].setWall();
    world[0][3][2][0].setWall();
    world[0][3][2][3].setWall();
    world[0][3][3][0].setWall();
    world[0][3][3][1].setWall();
    // Doorway: leave (3,2) and (3,3) open as entrance from bottom
    world[0][3][3][2].setEmpty();
    world[0][3][3][3].setEmpty();

    // --- Block (1,2): Machine room ---
    world[1][2][0][0].setWall();
    world[1][2][0][1].setWall();
    world[1][2][0][2].setWall();
    world[1][2][0][3].setWall();
    world[1][2][1][0].setWall();
    world[1][2][1][3].setWall();
    world[1][2][2][0].setWall();
    world[1][2][2][3].setWall();
    world[1][2][3][0].setWall();
    world[1][2][3][2].setWall();
    world[1][2][3][3].setWall();
    // Doorway: (3,1) open

    // --- Block (3,3): Final zone — walled off until triggered ---
    world[3][3][0][0].setWall();
    world[3][3][0][1].setWall();
    world[3][3][0][2].setWall();
    world[3][3][0][3].setWall();
    world[3][3][1][0].setWall();
    world[3][3][1][3].setWall();
    world[3][3][2][0].setWall();
    world[3][3][2][3].setWall();
    world[3][3][3][0].setWall();
    world[3][3][3][1].setWall();
    world[3][3][3][2].setWall();
    world[3][3][3][3].setWall();
    // Fully sealed for now — you'll unlock the entrance programmatically later
}

bool Map::isWalkable(int br, int bc, int r, int c)
{
    if (br < 0 || br >= WORLD_SIZE || bc < 0 || bc >= WORLD_SIZE)
        return false;

    if (r < 0 || r >= BLOCK_SIZE || c < 0 || c >= BLOCK_SIZE)
        return false;

    return world[br][bc][r][c].isWalkable();
}

void Map::print(int playerBr, int playerBc, int playerR, int playerC)
{
    const int VIEW_SIZE = 7;
    int half = VIEW_SIZE / 2;

    int playerGR = toGlobalRow(playerBr, playerR);
    int playerGC = toGlobalCol(playerBc, playerC);

    int worldSize = WORLD_SIZE * BLOCK_SIZE;

    int startR = playerGR - half;
    int startC = playerGC - half;

    int endR = playerGR + half;
    int endC = playerGC + half;

    if (startR < 0)
        startR = 0;
    if (startC < 0)
        startC = 0;

    if (endR >= worldSize)
        endR = worldSize - 1;
    if (endC >= worldSize)
        endC = worldSize - 1;

    cout << "\n--- CAMERA VIEW ---\n";

    for (int gr = startR; gr <= endR; gr++)
    {
        for (int gc = startC; gc <= endC; gc++)
        {
            Tile &tile = getTileGlobal(gr, gc);

            if (tile.getOccupant() != nullptr)
                cout << tile.getOccupant()->getSymbol() << " ";
            else if (tile.getObject() != nullptr)
                cout << tile.getObject()->getSymbol() << " ";
            else
                cout << tile.getSymbol() << " ";
        }
        cout << endl;
    }
}

int Map::toGlobalRow(int br, int r)
{
    return br * BLOCK_SIZE + r;
}

int Map::toGlobalCol(int bc, int c)
{
    return bc * BLOCK_SIZE + c;
}

void Map::toLocal(int gr, int gc, int &br, int &bc, int &r, int &c)
{
    br = gr / BLOCK_SIZE;
    bc = gc / BLOCK_SIZE;
    r = gr % BLOCK_SIZE;
    c = gc % BLOCK_SIZE;
}

void Map::openFinalZone()
{
    world[3][3][0][1].setEmpty();
    world[3][3][0][2].setEmpty();
}
