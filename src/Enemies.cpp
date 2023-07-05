#include "Enemies.h"
#include "Components.h"
#include "Player.h"

#include "raylib.h"
#include "raymath.h"
#include <algorithm>
#include <cstddef>

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
    for (size_t i = 0; i < numOfRays; i++) {
        if (context.dangers[i] > 0.0f) {
            context.interests[i] = 0.0f;
        }
    }
    Vector2 chosenDir = {0};
    for (size_t i = 0; i < numOfRays; i++) {
        chosenDir.x += context.rays[i].x * context.interests[i];
        chosenDir.y += context.rays[i].y * context.interests[i];
    }

    TraceLog(LOG_INFO, "x: %f y: %f", chosenDir.x, chosenDir.y);

    vel.current = 150.0f;

    vel.UpdateAngle(chosenDir);
    Vector2 moveVector = Vector2Rotate(Vector2{0.0f, -vel.current}, vel.angle);
    vel.x = moveVector.x;
    vel.y = moveVector.y;

    hitbox.x += vel.x * frameTime;
    hitbox.y += vel.y * frameTime;
}

void Enemy::Draw() const {
    hitbox.DrawHitBox(sprite.color);
    context.DrawRays(hitbox.GetCenter());
}

// void Enemy::CalcWeight(const HitBoxRect &target) {
//     float targetRight = (hitbox.x + hitbox.width) - target.x;
//     float targetLeft = hitbox.x - (target.x + target.width);
//     bool intersectsX =
//         CheckAxisIntersections(hitbox.x, hitbox.width, target.x,
//         target.width);
//     float x = (intersectsX)                                    ? 0
//               : (std::abs(targetRight) < std::abs(targetLeft)) ? targetRight
//                                                                : targetLeft;
//     float targetUp = hitbox.y - (target.y + target.height);
//     float targetDown = (hitbox.y + hitbox.height) - target.y;
//     bool intersectsY = CheckAxisIntersections(hitbox.y, hitbox.height,
//     target.y,
//                                               target.height);
//     float y = (intersectsY)                                 ? 0
//               : (std::abs(targetUp) < std::abs(targetDown)) ? targetUp
//                                                             : targetDown;

//     float vecLength = Vector2Length({x, y}) + 0.001f;

//     TraceLog(LOG_INFO, "x: %f, y: %f, length: %f", x, y, vecLength);

//     const float priority = 100.0f * sgn(type);

//     if (vecLength > 20.5f) {
//         movementWeight.x += priority / vecLength * sgn(x);
//         movementWeight.y += priority / vecLength * sgn(y);
//     }
// }

// void Enemy::ResetWeight() {
//     movementWeight.x = 0.0f;
//     movementWeight.y = 0.0f;
// }

void Enemy::AddToContext(const HitBoxRect &target) {
    switch (target.type) {
    case PLAYER: {
        for (size_t i = 0; i < numOfRays; i++) {
            Vector2 targetVec = target.GetCenter();
            targetVec.x -= hitbox.x;
            targetVec.y -= hitbox.y;
            float dot = Vector2DotProduct(context.rays[i], targetVec);
            TraceLog(LOG_INFO, "i: %d dot: %f", i, dot);
            context.interests[i] = std::max(0.0f, dot);
        }
        break;
    }
    case WALL:
        break;
    case ENEMY:
        break;
    default:
        break;
    }
}

void Enemy::PopulateContext() {
    for (size_t i = 0; i < numOfRays; i++) {
        const float angle = i * 2 * PI / numOfRays;
        context.rays[i] = Vector2Rotate({0.0f, -1.0f}, angle);
        context.interests[i] = 0.5f;
        context.dangers[i] = 0.0f;
    }
}
