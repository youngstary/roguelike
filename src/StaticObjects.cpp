#include "StaticObjects.h"
#include "Components.h"

Wall::Wall(float x, float y, float width, float height)
    : hitbox({x, y, width, height, EntityType::WALL}) {}

void Wall::Draw() const { hitbox.DrawHitBox(GREEN); }