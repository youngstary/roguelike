#include "entt.hpp"
#include "raylib.h"

struct Player {
    float cursorRadius;
};

struct Position {
    Vector2 value;
};

struct Sprite {
    Rectangle rect;
    Color color;
};

struct Velocity {
    Vector2 current;
    float max;
    float acc;
    float dAcc;
};

struct CursorPos {
    Vector2 pos;
    float radius = 10;
};

struct CameraFocus {};

entt::entity MakePlayer(entt::registry &, float, float);
void UpdatePlayerVelocity(entt::registry &);
void UpdatePositions(entt::registry &);
void UpdatePointer(entt::registry &);
