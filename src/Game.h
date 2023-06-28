#include "entt.hpp"
#include "raylib.h"

class Game {
  public:
    Game(int, int);
    int MainLoop();
    void Update();
    void UpdateCamera2D();
    void Draw();
    void DrawSprites();
    void DrawCursor();

    Camera2D camera = {0};

    entt::registry reg;
};
