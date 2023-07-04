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
    Velocity vel;
    float lastPosX;
    Health health;
    HitBoxCircle cursor;
    Sprite sprite;
};
