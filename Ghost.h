#ifndef GHOST_H
#define GHOST_H

#include "GhostState.h"

class Ghost {
public:
    int x, y;
    GhostState*state;

    Ghost(int startX, int startY);
    void Move(int dx, int dy);
    void SetState(GhostState* newState);
    void Update();
};

#endif
