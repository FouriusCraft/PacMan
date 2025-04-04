#include "GhostState.h"
#include "Ghost.h"
#include "Pacman.h"
#include <cstdlib>
#include <cmath>

// ChaseState
void ChaseState::Move(Ghost* ghost) {
    extern Pacman pacman;

    int dx = pacman.x - ghost->x;
    int dy = pacman.y - ghost->y;

    if (std::abs(dx) > std::abs(dy)) {
        ghost->Move(dx > 0 ? 1 : -1, 0);
    }
    else {
        ghost->Move(0, dy > 0 ? 1 : -1);
    }
}

// WanderState
void WanderState::Move(Ghost* ghost) {
    int dx = (rand() % 3) - 1;
    int dy = (rand() % 3) - 1;
    ghost->Move(dx, dy);
}

// FrightenedState
void FrightenedState::Move(Ghost* ghost) {
    int dx = (rand() % 3) - 1;
    int dy = (rand() % 3) - 1;
    ghost->Move(dx, dy);
}

// ReturnToBaseState
void ReturnToBaseState::Move(Ghost* ghost) {
    // Contoh logika sederhana: kembalikan ke posisi (9,9)
    int dx = 9 - ghost->x;
    int dy = 9 - ghost->y;

    if (std::abs(dx) > std::abs(dy)) {
        ghost->Move(dx > 0 ? 1 : -1, 0);
    }
    else if (dy != 0) {
        ghost->Move(0, dy > 0 ? 1 : -1);
    }
}
