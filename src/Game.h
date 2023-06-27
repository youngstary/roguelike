#include "raylib.h"

#include "Player.h"

class Game {
  public:
    Game(int, int);
    int MainLoop();
    void Update();
    void UpdateCamera2D(Vector2 targetPos);
    void Draw();

    Player player;
    Camera2D camera = {0};
};
