#include "GhostFactory.h"
#include <iostream>

Ghost* GhostFactory::CreateGhost(const std::string& type, int startX, int startY) {
    if (type == "Blinky") {
        return new Ghost(startX, startY); // Nanti bisa dikustomisasi
    }
    else if (type == "Pinky") {
        return new Ghost(startX, startY);
    }
    else if (type == "Inky") {
        return new Ghost(startX, startY);
    }
    else if (type == "Clyde") {
        return new Ghost(startX, startY);
    }
    else {
        std::cout << "Unknown ghost type: " << type << std::endl;
        return nullptr;
    }
}
