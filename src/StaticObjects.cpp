#include "StaticObjects.h"

Wall::Wall(float x, float y, float width, float height)
    : hitbox({x, y, width, height}) {}

void Wall::Draw() const { hitbox.DrawHitBox(GREEN); }