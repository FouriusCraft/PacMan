#ifndef GHOST_H
#define GHOST_H

class Ghost {
public:
    int x, y; // Posisi dalam grid
    Ghost(int startX, int startY);
    void Move(int dx, int dy);
};

#endif
