#include "raylib.h"
#include "config.h"
#include "Map.h"
#include "Pacman.h"
#include "GhostFactory.h"
#include "GhostState.h"
#include "GhostDecorator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Objek global sederhana untuk demo
Map gameMap;
Pacman pacman(1, 1);
Ghost* ghost = nullptr;

// Objek state yang digunakan secara statis
ChaseState chaseState;
WanderState wanderState;
FrightenedState frightenedState;
ReturnToBaseState returnToBaseState;

// Perhatikan: Di GhostState.cpp, objek global "pacman" dan "gameMap" diakses via extern.
static GhostState* currentGhostState = &wanderState;

int main() {
    // Inisialisasi seed random
    srand(static_cast<unsigned int>(time(NULL)));

    // Buat ghost menggunakan factory; posisi awal: pojok kanan dekat atas
    ghost = GhostFactory::CreateGhost("Blinky", COLS - 2, 1);
    ghost->SetState(&wanderState);
    std::string currentStateName = "Wander";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man");
    SetTargetFPS(10); // FPS yang lebih rendah untuk memudahkan observasi


    while (!WindowShouldClose()) {
        // --- Update Game ---
        // Update pergerakan Pacman menggunakan WASD
        int newX = pacman.x;
        int newY = pacman.y;
        if (IsKeyPressed(KEY_D)) newX++;
        if (IsKeyPressed(KEY_A)) newX--;
        if (IsKeyPressed(KEY_W)) newY--;
        if (IsKeyPressed(KEY_S)) newY++;
        if (gameMap.IsWalkable(newX, newY))
            pacman.Move(newX - pacman.x, newY - pacman.y);

        // Ubah state ghost berdasarkan input
        // Ganti state hanya saat tombol ditekan
        static GhostState* currentGhostState = &wanderState;

        // Ganti state hanya saat tombol ditekan
        if (IsKeyPressed(KEY_C)) {
            currentGhostState = &chaseState;
            currentStateName = "Chase";
        }
        if (IsKeyPressed(KEY_F)) {
            currentGhostState = &frightenedState;
            currentStateName = "Frightened";
        }
        if (IsKeyPressed(KEY_R)) {
            currentGhostState = &returnToBaseState;
            currentStateName = "Return";
        }
        if (IsKeyPressed(KEY_V)) {
            currentGhostState = &wanderState;
            currentStateName = "Wander";
        }



        // Apply state ke ghost

        // Toggle Speed Boost decorator:
        if (IsKeyPressed(KEY_B)) {
            // Bungkus ghost dengan SpeedBoostDecorator
            ghost = new SpeedBoostDecorator(ghost);
        }
        // Lepaskan boost jika tombol N ditekan
        if (IsKeyPressed(KEY_N)) {
            SpeedBoostDecorator* decorator = dynamic_cast<SpeedBoostDecorator*>(ghost);
            if (decorator) {
                ghost = decorator->_ghost;
                decorator->_ghost = nullptr;
                delete decorator;
            }
        }
        ghost->SetState(currentGhostState);

        // Update ghost (pergerakan berdasarkan state aktif)
        ghost->Update();

        // --- Draw Game ---
        BeginDrawing();
        ClearBackground(BLACK);

        // Gambar peta
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                char cell = gameMap.grid[i][j];
                if (cell == '#') {
                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
                    DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, BLACK);
                }
                else if (cell == '.') {
                    DrawCircle(x + TILE_SIZE / 2, y + TILE_SIZE / 2, TILE_SIZE / 8, WHITE);
                }
            }
        }


        DrawText("Controls:", 10, 10, 20, LIGHTGRAY);
        DrawText("WASD: Move Pac-Man", 10, 30, 18, GRAY);
        DrawText("C: Chase State", 10, 50, 18, GRAY);
        DrawText("F: Frightened State", 10, 70, 18, GRAY);
        DrawText("R: Return to Base", 10, 90, 18, GRAY);
        DrawText("V: Wander State", 10, 110, 18, GRAY);
        DrawText("B: Boost ON", 10, 130, 18, GRAY);
        DrawText("N: Boost OFF", 10, 150, 18, GRAY);

        // Gambar Pacman
        DrawCircle(pacman.x * TILE_SIZE + TILE_SIZE / 2, pacman.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, YELLOW);

        // Gambar Ghost
        DrawCircle(ghost->x * TILE_SIZE + TILE_SIZE / 2, ghost->y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 3, RED);
        DrawText(("Current Ghost State: " + currentStateName).c_str(), 10, SCREEN_HEIGHT - 30, 20, WHITE);
        // Cek apakah ghost saat ini menggunakan SpeedBoostDecorator
        bool isBoosted = dynamic_cast<SpeedBoostDecorator*>(ghost) != nullptr;
        std::string boostText = isBoosted ? "Boost: ON" : "Boost: OFF";

        // Tampilkan teks status boost
        DrawText(boostText.c_str(), 10, SCREEN_HEIGHT - 60, 20, isBoosted ? RED : GRAY);

        EndDrawing();
    }

    // Bersihkan memori
    delete ghost;
    CloseWindow();
    return 0;
}
