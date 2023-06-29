#pragma once
#include "raylib.h"

enum EntityType { PLAYER = 0, WALL };

struct HitBoxRect : Rectangle {
    Vector2 GetPosition() const { return Vector2{x, y}; };
    Vector2 GetCenter() const {
        return Vector2{x + width / 2, y + height / 2};
    };
    Rectangle BeforeMoveX(float velocityX) const {
        return {x - velocityX, y, width, height};
    };
    void DrawHitBox(Color color) const {
        DrawRectangleRec({x, y, width, height}, color);
    };
};

struct HitBoxCircle : Vector2 {
    float radius;
    Vector2 GetPosition() const { return Vector2{x, y}; };
    void DrawHitBox(Color color) const { DrawCircleV({x, y}, radius, color); };
};

struct Velocity : Vector2 {
    float max;
    float acc;
    float dAcc;
};

struct Sprite {
    Vector2 offset;
    Color color;
    // Texture2D* texture;
};