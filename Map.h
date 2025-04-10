#ifndef MAP_H
#define MAP_H

#include "config.h"

class Map {
public:
    char grid[ROWS][COLS];
    Map();
    void LoadMap();
    bool IsWalkable(int x, int y) const;
};

#endif
