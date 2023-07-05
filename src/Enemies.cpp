#include "Enemies.h"
#include "Components.h"
#include "Player.h"

#include "raylib.h"
#include "raymath.h"
#include <algorithm>

int sgn(float val) { return (0.0f <= val) - (val < 0.0f); }

bool CheckAxisIntersections(float a1, float len1, float a2, float len2) {
    return (a1 > a2 && a1 < a2 + len2) ||
           (a1 + len1 > a2 && a1 + len1 < a2 + len2) ||
           (a1 < a2 && a2 + len2 < a1 + len1) ||
           (a2 < a1 && a1 + len1 < a2 + len2);
}

Enemy::Enemy(float x, float y, EnemyType type) : type(type) {
    hitbox.type = EntityType::ENEMY;
    hitbox.x = x;
    hitbox.y = y;
    vel.x = 0;
    vel.y = 0;

    switch (type) {
    case MELEE:
        hitbox.width = 64.0f;
        hitbox.height = 64.0f;

        vel.acc = 50.0f;
        vel.dAcc = 60.0f;
        vel.max = 200.0f;

        health.number = 5;

        sprite.offset = {0};
        sprite.color = RED;
        break;
    case RANGER:
        hitbox.width = 32.0f;
        hitbox.height = 64.0f;

        vel.acc = 50.0f;
        vel.dAcc = 60.0f;
        vel.max = 200.0f;

        health.number = 3;

        sprite.offset = {0};
        sprite.color = PURPLE;
        break;
    default:
        break;
    }
}

void Enemy::Move(const float frameTime) {
    TraceLog(LOG_INFO, "Final weight: %f %f", movementWeight.x,
             movementWeight.y);

    if (std::abs(movementWeight.x) > 1.5f ||
        std::abs(movementWeight.y) > 1.5f) {
        vel.current += vel.acc;
    } else if (vel.current > 0) {
        vel.current = (vel.current - vel.dAcc < 0) ? 0 : vel.current - vel.dAcc;
    }
    if (vel.current > vel.max) {
        vel.current = vel.max;
    }

    vel.UpdateAngle(movementWeight);
    Vector2 moveVector = Vector2Rotate(Vector2{0.0f, -vel.current}, vel.angle);
    vel.x = moveVector.x;
    vel.y = moveVector.y;

    hitbox.x += vel.x * frameTime;
    hitbox.y += vel.y * frameTime;
}

void Enemy::Draw() const { hitbox.DrawHitBox(sprite.color); }

void Enemy::CalcWeight(const HitBoxRect &target) {
    float targetRight = (hitbox.x + hitbox.width) - target.x;
    float targetLeft = hitbox.x - (target.x + target.width);
    bool intersectsX =
        CheckAxisIntersections(hitbox.x, hitbox.width, target.x, target.width);
    float x = (intersectsX)                                    ? 0
              : (std::abs(targetRight) < std::abs(targetLeft)) ? targetRight
                                                               : targetLeft;
    float targetUp = hitbox.y - (target.y + target.height);
    float targetDown = (hitbox.y + hitbox.height) - target.y;
    bool intersectsY = CheckAxisIntersections(hitbox.y, hitbox.height, target.y,
                                              target.height);
    float y = (intersectsY)                                 ? 0
              : (std::abs(targetUp) < std::abs(targetDown)) ? targetUp
                                                            : targetDown;

    float vecLength = Vector2Length({x, y}) + 0.001f;

    TraceLog(LOG_INFO, "x: %f, y: %f, length: %f", x, y, vecLength);

    const float priority = 100.0f;

    movementWeight.x += priority / vecLength * sgn(x) * sgn(type);
    movementWeight.y += priority / vecLength * sgn(y) * sgn(type);
}

void Enemy::ResetWeight() {
    movementWeight.x = 0.0f;
    movementWeight.y = 0.0f;
}
