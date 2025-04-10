#ifndef GHOST_STATE_H
#define GHOST_STATE_H

class Ghost; // Forward declaration

class GhostState {
public:
    virtual void Move(Ghost* ghost) = 0;
    virtual ~GhostState() {}
};

// State ketika ghost mengejar Pacman
class ChaseState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// State ketika ghost bergerak acak
class WanderState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// State ghost setelah Pacman makan power pellet (bergerak erratik)
class FrightenedState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// State ghost kembali ke markas
class ReturnToBaseState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

#endif
