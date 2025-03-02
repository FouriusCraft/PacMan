#ifndef PACMAN_H
#define PACMAN_H

class Pacman {
public:
    int x, y; // Posisi dalam grid
    Pacman(int startX, int startY);
    void Move(int dx, int dy);
};

#endif
