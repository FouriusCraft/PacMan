#include "Ghost.h"

Ghost::Ghost(int startX, int startY) : x(startX), y(startY) {}

void Ghost::Move(int dx, int dy) {
    x += dx;
    y += dy;
}
