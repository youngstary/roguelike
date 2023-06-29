#pragma once

#include "Components.h"
#include "raylib.h"

class Player {
  public:
    Player(){};
    Player(float x, float y);
    void Move(const float frameTime);
    void UpdatePointer(Camera2D *);
    void Draw() const;
    void Collision(EntityType type, HitBoxRect hitbox);

    HitBoxRect hitbox;
    Velocity vel = {0.0f, 0.0f, 200.0f, 60.0f, 80.0f};
    float lastPosX;
    HitBoxCircle cursor;
    Sprite sprite;
};
