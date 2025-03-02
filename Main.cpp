#include <raylib.h>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"

#define TILE_SIZE 50  
#define SCREEN_WIDTH (COLS * TILE_SIZE)
#define SCREEN_HEIGHT (ROWS * TILE_SIZE)

Map gameMap;
Pacman pacman(1, 1); // Spawn Pacman di posisi awal
Ghost ghost(9, 9); // Spawn Ghost di posisi awal

void DrawGame() {
    // Gambar peta
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            switch (gameMap.grid[i][j]) {
            case '#': // Tembok
                DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, BLACK);
                break;
            case '.': // Titik kecil (makanan)
                DrawCircle(x + TILE_SIZE / 2, y + TILE_SIZE / 4, TILE_SIZE / 8, WHITE);
                break;
            }
        }
    }

    // Gambar Pacman
    DrawCircle(pacman.x * TILE_SIZE + TILE_SIZE / 2, pacman.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, YELLOW);

    // Gambar Ghost
    DrawCircle(ghost.x * TILE_SIZE + TILE_SIZE / 2, ghost.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, RED);
}

void UpdateGame() {
    if (IsKeyPressed(KEY_RIGHT) && gameMap.grid[pacman.y][pacman.x + 1] != '#') pacman.Move(1, 0);
    if (IsKeyPressed(KEY_LEFT) && gameMap.grid[pacman.y][pacman.x - 1] != '#') pacman.Move(-1, 0);
    if (IsKeyPressed(KEY_UP) && gameMap.grid[pacman.y - 1][pacman.x] != '#') pacman.Move(0, -1);
    if (IsKeyPressed(KEY_DOWN) && gameMap.grid[pacman.y + 1][pacman.x] != '#') pacman.Move(0, 1);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
