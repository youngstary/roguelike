#pragma once
#include <vector>

#include "raylib.h"

#include "Components.h"
#include "Enemies.h"
#include "Gui.h"
#include "Player.h"
#include "StaticObjects.h"

struct Game {
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
    void ChangeState(State nextState);
    void TooglePause(State nextState);
    void CalcEnemyMovWeight(size_t i);

    Player player;
    std::vector<Wall> walls;
    std::vector<Enemy> enemies;
    Camera2D camera = {0};
    State currentState;
    State nextState = currentState;

    Gui gui;
};
