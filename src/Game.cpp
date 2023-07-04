#include "Game.h"
#include "Gui.h"

Game::Game(int screenWidth, int screenHeight) : currentState(PLAYING) {
    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");
    SetTargetFPS(60);
    SetExitKey(KEY_F11);
    gui.Init(currentState);
}

Game::~Game() { DestroyLevel(); }

int Game::MainLoop() {
    InitLevel();
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        nextState = currentState;
        Update();
        Draw();
        currentState = nextState;
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void Game::Update() {
    switch (currentState) {
    case PLAYING: {
        TooglePause(PAUSE);
        const float frameTime = GetFrameTime();
        // Player
        player.Move(frameTime);
        player.UpdatePointer(&camera);

        CheckCollisions();

        // Camera
        UpdateCamera2D(player.hitbox.GetPosition());

        break;
    }
    case PAUSE:
        TooglePause(PLAYING);
        break;
    default:
        TraceLog(LOG_WARNING, "Case not handled: %d", currentState);
        break;
    }
}

void Game::UpdateCamera2D(Vector2 targetPos) { camera.target = targetPos; }

void Game::Draw() {
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);

    for (const auto &wall : walls) {
        wall.Draw();
    }

    player.Draw();

    EndMode2D();
    // Draw GUI
    const State result = gui.Draw(currentState);

    if (result != currentState) {
        ChangeState(result);
        gui.ChangeLayout(result);
    } else if (nextState != currentState) {
        gui.ChangeLayout(nextState);
    }

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

void Game::ChangeState(State nextState) { this->nextState = nextState; }

void Game::TooglePause(State nextState) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        ChangeState(nextState);
    }
}