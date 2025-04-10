#include "GhostState.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Map.h"
#include "config.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

// Objek global agar dapat diakses di state
extern Pacman pacman;
extern Map gameMap;

// ------------------------
// ChaseState: mengejar Pacman
// ------------------------
void ChaseState::Move(Ghost* ghost) {
    

    //print Chase state ke console pake c++
	

    int dx = pacman.x - ghost->x;
    int dy = pacman.y - ghost->y;

    // Tentukan prioritas gerakan berdasarkan mana yang lebih jauh
    int primaryX = 0, primaryY = 0;
    int secondaryX = 0, secondaryY = 0;

    if (std::abs(dx) > std::abs(dy)) {
        primaryX = (dx > 0) ? 1 : -1;
        secondaryY = (dy > 0) ? 1 : (dy < 0 ? -1 : 0);
    }
    else {
        primaryY = (dy > 0) ? 1 : -1;
        secondaryX = (dx > 0) ? 1 : (dx < 0 ? -1 : 0);
    }

    // Coba gerakan utama
    int newX = ghost->x + primaryX;
    int newY = ghost->y + primaryY;
    if (gameMap.IsWalkable(newX, newY)) {
        ghost->Move(primaryX, primaryY);
        return;
    }

    // Jika gerakan utama terhalang, coba gerakan alternatif
    newX = ghost->x + secondaryX;
    newY = ghost->y + secondaryY;
    if (gameMap.IsWalkable(newX, newY)) {
        ghost->Move(secondaryX, secondaryY);
        return;
    }

    // Jika kedua arah utama terhalang, coba semua arah yang mungkin
    int dirs[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    for (int i = 0; i < 4; i++) {
        newX = ghost->x + dirs[i][0];
        newY = ghost->y + dirs[i][1];
        if (gameMap.IsWalkable(newX, newY)) {
            ghost->Move(dirs[i][0], dirs[i][1]);
            return;
        }
    }
    // Jika tidak ada arah valid, ghost tetap di tempat.
}

// ------------------------
// WanderState: gerakan acak dengan validasi
// ------------------------
void WanderState::Move(Ghost* ghost) {
    // Daftar empat arah yang memungkinkan
    int dirs[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

    // Acak urutan arah
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp0 = dirs[i][0];
        int temp1 = dirs[i][1];
        dirs[i][0] = dirs[r][0];
        dirs[i][1] = dirs[r][1];
        dirs[r][0] = temp0;
        dirs[r][1] = temp1;
    }
    // Coba masing-masing arah hingga menemukan gerakan valid
    for (int i = 0; i < 4; i++) {
        int newX = ghost->x + dirs[i][0];
        int newY = ghost->y + dirs[i][1];
        if (gameMap.IsWalkable(newX, newY)) {
            ghost->Move(dirs[i][0], dirs[i][1]);
            return;
        }
    }
    // Jika semua arah terhalang, ghost tidak bergerak.
}

// ------------------------
// FrightenedState: menggunakan logika acak seperti WanderState
// ------------------------
void FrightenedState::Move(Ghost* ghost) {
    // Untuk membuat pergerakan lebih unpredictable, kita panggil WanderState
    WanderState w;
    w.Move(ghost);
}

// ------------------------
// ReturnToBaseState: kembalikan ghost ke markas (misal pojok kanan bawah)
// ------------------------
void ReturnToBaseState::Move(Ghost* ghost) {
    int baseX = COLS - 2;
    int baseY = ROWS - 2;
    int dx = baseX - ghost->x;
    int dy = baseY - ghost->y;
    int moveX = (dx != 0) ? (dx > 0 ? 1 : -1) : 0;
    int moveY = (dy != 0) ? (dy > 0 ? 1 : -1) : 0;
    int newX = ghost->x + moveX;
    int newY = ghost->y + moveY;
    if (gameMap.IsWalkable(newX, newY))
        ghost->Move(moveX, moveY);
}
