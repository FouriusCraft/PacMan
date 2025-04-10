#include "GhostDecorator.h"
#include "config.h"
#include "raylib.h"

GhostDecorator::GhostDecorator(Ghost* ghost) : Ghost(ghost->x, ghost->y), _ghost(ghost) {}

GhostDecorator::~GhostDecorator() {
    delete _ghost;
}

void GhostDecorator::Update() {
    _ghost->Update();
    x = _ghost->x;
    y = _ghost->y;
}

SpeedBoostDecorator::SpeedBoostDecorator(Ghost* ghost) : GhostDecorator(ghost) {}

SpeedBoostDecorator::~SpeedBoostDecorator() {}

void SpeedBoostDecorator::Update() {
    // Update dua kali untuk efek speed boost.
    _ghost->Update();
    _ghost->Update();
    x = _ghost->x;
    y = _ghost->y;
}
