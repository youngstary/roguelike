#pragma once
#include <vector>

#include "raylib.h"

#include "Components.h"
#include "Player.h"
#include "StaticObjects.h"

class Game {
  public:
    Game(int screenWidth, int screenHeight);
    ~Game();
    int MainLoop();
    void Update();
    void UpdateCamera2D(Vector2 targetPos);
    void Draw();
    void InitLevel();
    void DestroyLevel();
    void CheckCollisions();
    void PlayerCollisions();

    Player player;
    std::vector<Wall> walls;
    Camera2D camera = {0};
};
