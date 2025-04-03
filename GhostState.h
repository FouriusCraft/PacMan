#ifndef GHOST_STATE_H
#define GHOST_STATE_H

class Ghost; // Forward declaration

class GhostState {
public:
    virtual void Move(Ghost* ghost) = 0; 
    virtual ~GhostState() {}
};

// Ghost mengejar Pac-Man
class ChaseState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// Ghost bergerak secara acak
class WanderState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// Ghost run setelah Pac-Man makan power pellet
class FrightenedState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

// Ghost kembali ke rumah setelah dimakan
class ReturnToBaseState : public GhostState {
public:
    void Move(Ghost* ghost) override;
};

#endif
