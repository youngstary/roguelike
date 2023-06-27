#include "math.h"
#include "raylib.h"

class Player {
  public:
    Player(float x, float y);
    void Move();
    void UpdatePointer(Camera2D *);
    void Draw();

    Vector2 pos;
    Vector2 vel = {0.0f, 0.0f};
    Vector2 ptrPos = pos;

    float maxVelocity = 4.0f;
    float acc = 0.3f;
    float dAcc = 0.4f;

    float radius = 20;
    float ptrRadius = 10;
    float borderRadius = 45;

    float angle = 0.0f;
};
