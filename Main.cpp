#include <raylib.h>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostFactory.h"
#include "GhostState.h"
#include <iostream>

#define TILE_SIZE 50  
#define SCREEN_WIDTH (COLS * TILE_SIZE)
#define SCREEN_HEIGHT (ROWS * TILE_SIZE)

Map gameMap;
Pacman pacman(1, 1);

//  Factory Method create  Ghost
Ghost* ghost = GhostFactory::CreateGhost("Blinky", 9, 9);

ChaseState chaseState;
WanderState wanderState;
FrightenedState frightenedState;

void DrawGame() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            switch (gameMap.grid[i][j]) {
            case '#':
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, BLACK);
                break;
            case '.':
                DrawCircle(x + TILE_SIZE / 2, y + TILE_SIZE / 2, TILE_SIZE / 8, WHITE);
                break;
            }
        }
    }

    DrawCircle(pacman.x * TILE_SIZE + TILE_SIZE / 2, pacman.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, YELLOW);

    if (ghost) {
        DrawCircle(ghost->x * TILE_SIZE + TILE_SIZE / 2, ghost->y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, RED);
    }
}

void UpdateGame() {
    int newX = pacman.x;
    int newY = pacman.y;

    if (IsKeyPressed(KEY_RIGHT)) newX++;
    if (IsKeyPressed(KEY_LEFT)) newX--;
    if (IsKeyPressed(KEY_UP)) newY--;
    if (IsKeyPressed(KEY_DOWN)) newY++;

    if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS && gameMap.grid[newY][newX] != '#') {
        pacman.Move(newX - pacman.x, newY - pacman.y);
    }

    if (IsKeyPressed(KEY_F)) {
        ghost->SetState(&frightenedState);
    }
    else if (IsKeyPressed(KEY_C)) {
        ghost->SetState(&chaseState);
    }
    else {
        ghost->SetState(&wanderState);
    }

    ghost->Update();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man");
    SetTargetFPS(60);
	std::cout << "hi" << std::endl;
    while (!WindowShouldClose()) {
        UpdateGame();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawGame();
        EndDrawing();
    }

    delete ghost;
    CloseWindow();
    return 0;
}
