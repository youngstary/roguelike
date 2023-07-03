#pragma once
#include "Components.h"

class Wall {
  public:
    Wall(float x, float y, float width, float height);
    void Draw() const;

    HitBoxRect hitbox;
    Sprite sprite;
};