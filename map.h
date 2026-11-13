#ifndef MAP_H
#define MAP_H

#include "tile.h"

class Map
{
private:
    static const int WORLD_SIZE = 4;
    static const int BLOCK_SIZE = 4;

    Tile world[WORLD_SIZE][WORLD_SIZE][BLOCK_SIZE][BLOCK_SIZE];

public:
    Map();

    void generateMap();

    bool isWalkable(int br, int bc, int r, int c);

    void print(int playerBr, int playerBc, int playerR, int playerC);

    Tile &getTile(int br, int bc, int r, int c);

    Tile &getTileGlobal(int gr, int gc);

    int toGlobalRow(int br, int r);

    int toGlobalCol(int bc, int c);
    static int getBlockSize() { return 4; }
    void toLocal(int gr, int gc, int &br, int &bc, int &r, int &c);

    void openFinalZone();
};

#endif
