#ifndef GHOST_DECORATOR_H
#define GHOST_DECORATOR_H

#include "Ghost.h"

// Kelas dasar decorator yang membungkus objek Ghost.
// (Untuk kesederhanaan, variabel _ghost dibuat public.)
class GhostDecorator : public Ghost {
public:
    Ghost* _ghost;
    GhostDecorator(Ghost* ghost);
    virtual ~GhostDecorator();
    virtual void Update() override;
};

// Decorator untuk menambah kecepatan ghost (speed boost)
class SpeedBoostDecorator : public GhostDecorator {
public:
    SpeedBoostDecorator(Ghost* ghost);
    virtual ~SpeedBoostDecorator();
    virtual void Update() override; // Memanggil update dua kali untuk simulasi speed boost.
};

#endif
