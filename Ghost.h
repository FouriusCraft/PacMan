#ifndef GHOST_H
#define GHOST_H

#include "GhostState.h"

class Ghost {
public:
    int x, y;
    GhostState* state;
    Ghost(int startX, int startY);
    virtual ~Ghost();
    virtual void Move(int dx, int dy);
    virtual void SetState(GhostState* newState);
    virtual void Update();
};

#endif
