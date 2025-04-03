#ifndef GHOST_STATE_H
#define GHOST_STATE_H

#include "Ghost.h"
#include "Pacman.h"
#include <cstdlib>
#include <cmath>

// State Interface
class GhostState {
public:
    virtual ~GhostState() = default;
    virtual void Move(Ghost* ghost) = 0;
};


class ChaseState : public GhostState {
public:
    void Move(Ghost* ghost) override {
        extern Pacman pacman; // Mengakses Pacman dari main

        int dx = pacman.x - ghost->x;
        int dy = pacman.y - ghost->y;

        if (std::abs(dx) > std::abs(dy)) {
            ghost->Move(dx > 0 ? 1 : -1, 0); // Prioritas ke kanan/kiri
        }
        else {
            ghost->Move(0, dy > 0 ? 1 : -1); // Prioritas ke atas/bawah
        }
    }
};


class WanderState : public GhostState {
public:
    void Move(Ghost* ghost) override {
        int dx = (rand() % 3) - 1; // -1, 0, 1
        int dy = (rand() % 3) - 1; // -1, 0, 1
        ghost->Move(dx, dy);
    }
};


class FrightenedState : public GhostState {
public:
    void Move(Ghost* ghost) override {
        int dx = (rand() % 3) - 1;
        int dy = (rand() % 3) - 1;
        ghost->Move(dx, dy);
    }
};

#endif
