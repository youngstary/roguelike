#include "raylib.h"
#include <vector>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Game.h"
#include "Player.h"

Game::Game(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    SetTargetFPS(60);
    GuiLoadStyleDefault();
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;
    MakePlayer(reg, screenWidth / 2.0f, screenHeight / 2.0f);
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
    UpdatePlayerVelocity(reg);
    UpdatePositions(reg);
    UpdatePointer(reg);
    UpdateCamera2D();
}

void Game::UpdateCamera2D() {
    auto view = reg.view<CameraFocus, Position>();
    for (auto entity : view) {
        auto &pos = view.get<Position>(entity).value;
        camera.target = pos;
        break;
    }
}

void Game::Draw() {
    auto view = reg.view<Player, Position>();
    for (auto entity : view) {
        const auto &pos = view.get<Position>(entity).value;
        if (pos.x != camera.target.x || pos.y != camera.target.y) {
            TraceLog(LOG_INFO, "Not the same %f, %f, %f, %f", pos.x, pos.y,
                     camera.target.x, camera.target.y);
        }
    }
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);
    DrawText("Start", 100, 100, 15, BLACK);
    DrawSprites();
    DrawCursor();

    EndMode2D();
    DrawFPS(10, 10); // Show current FPS
    EndDrawing();
}

void Game::DrawSprites() {
    auto view = reg.view<Position, Sprite>();
    for (auto entity : view) {
        const auto &pos = view.get<Position>(entity).value;
        const auto &sprite = view.get<Sprite>(entity);
        // DrawRectangle(pos.x, pos.y, sprite.rect.width, sprite.rect.height,
        //               sprite.color);
        DrawCircleV(pos, 15, RED);
    }
}

void Game::DrawCursor() {
    auto view = reg.view<CursorPos>();
    for (const auto entity : view) {
        const auto &cursor = view.get<CursorPos>(entity);
        DrawCircleV(cursor.pos, cursor.radius, BLUE);
    }
}
