#ifndef GHOST_FACTORY_H
#define GHOST_FACTORY_H

#include "Ghost.h"
#include <string>

class GhostFactory {
public:
    static Ghost* CreateGhost(const std::string& type, int startX, int startY);
};

#endif
