#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Game.h"

Game::Game(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    SetTargetFPS(60);
    GuiLoadStyleDefault();
}

Game::~Game() { DestroyLevel(); }

int Game::MainLoop() {
    InitLevel();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Update();
        Draw();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void Game::Update() {
    const float frameTime = GetFrameTime();
    // Player
    player.Move(frameTime);
    player.UpdatePointer(&camera);

    CheckCollisions();

    // Camera
    UpdateCamera2D(player.hitbox.GetPosition());
}

void Game::UpdateCamera2D(Vector2 targetPos) { camera.target = targetPos; }

void Game::Draw() {
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);

    player.Draw();

    for (const auto &wall : walls) {
        wall.Draw();
    }

    EndMode2D();
    // Draw GUI
    DrawFPS(10, 10); // Show current FPS

    EndDrawing();
}

void Game::InitLevel() {
    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    camera.offset = {screenWidth * 0.5f, screenHeight * 0.5f};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    player = Player(screenWidth * 0.5f, screenHeight * 0.5f);

    walls.emplace_back(Wall(0.0f, 0.0f, screenWidth, 100.0f));
    walls.emplace_back(Wall(0.0f, 150.0f, 100.0f, screenHeight));
}

void Game::DestroyLevel() { walls.clear(); }

void Game::CheckCollisions() {
    // Player - Walls
    for (const auto &wall : walls) {
        // Check if player is colliding with walls
        if (CheckCollisionRecs(player.hitbox, wall.hitbox)) {
            player.Collision(WALL, wall.hitbox);
            break;
        }
    }
}