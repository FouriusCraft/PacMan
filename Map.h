#ifndef MAP_H
#define MAP_H

#define ROWS 11
#define COLS 20

class Map {
public:
    char grid[ROWS][COLS];
    
    void LoadMap();
  Map();
};
#endif
