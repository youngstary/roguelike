#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Game.h"

Game::Game(int screenWidth, int screenHeight)
    : player(screenWidth / 2.0f, screenHeight / 2.0f) {
    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    SetTargetFPS(60);
    GuiLoadStyleDefault();
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;
}

int Game::MainLoop() {
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Update();
        Draw();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void Game::Update() {
    player.Move();
    player.UpdatePointer(&camera);
    UpdateCamera2D(player.pos);
}

void Game::UpdateCamera2D(Vector2 targetPos) { camera.target = targetPos; }

void Game::Draw() {
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);

    DrawFPS(10, 10); // Show current FPS

    player.Draw();

    EndMode2D();
    EndDrawing();
}
