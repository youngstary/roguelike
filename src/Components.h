#pragma once
#include "raylib.h"
#include <cmath>
#include <math.h>
#include <raymath.h>

class Game;
class Player;
class Enemy;
class Wall;

enum State { PLAYING, PAUSE, MAIN_MENU };

enum EntityType { PLAYER = 0, WALL };

struct HitBoxRect : Rectangle {
    Vector2 GetPosition() const { return Vector2{x, y}; }
    Vector2 GetCenter() const { return Vector2{x + width / 2, y + height / 2}; }
    Rectangle BeforeMoveX(float velocityX) const {
        return {x - velocityX, y, width, height};
    }
    void DrawHitBox(Color color) const {
        DrawRectangleRec({x, y, width, height}, color);
    }
};

struct HitBoxCircle : Vector2 {
    float radius;
    Vector2 GetPosition() const { return Vector2{x, y}; }
    void DrawHitBox(Color color) const { DrawCircleV({x, y}, radius, color); }
};

struct Velocity : Vector2 {
    float current;
    float angle;
    float max;
    float acc;
    float dAcc;
    void UpdateAngle(Vector2 vec) { angle = -atan2f(vec.x, vec.y) + PI; }
    void DrawVectorLine(float _x, float _y) const {
        DrawLine(_x, _y, _x + x, _y + y, ORANGE);
    }
};

struct Sprite {
    Vector2 offset;
    Color color;
    // Texture2D* texture;
};

struct Health {
    int number;
    void Heal(unsigned int amount) { number += amount; }
    void TakeDamage(unsigned int amount) { number -= amount; }
    bool IsDead() { return number <= 0; }
};