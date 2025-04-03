#include "Ghost.h"
#include <iostream>

Ghost::Ghost(int startX, int startY) : x(startX), y(startY), state(nullptr) {}

void Ghost::Move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Ghost::SetState(GhostState* newState) {
    state = newState;
}

void Ghost::Update() {
    if (state) {
        state->Move(this);
    }
}
