#include "Pacman.h"

Pacman::Pacman(int startX, int startY) : x(startX), y(startY) {}

void Pacman::Move(int dx, int dy) {
    x += dx;
    y += dy;
}
