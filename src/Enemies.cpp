#include "Enemies.h"
#include "Components.h"
#include "Player.h"

#include "raylib.h"
#include "raymath.h"

Enemy::Enemy(float x, float y, EnemyType type) : type(type) {
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

void Enemy::Move(const Player &player) {
    const Vector2 normVecToPlayer = Vector2Normalize(
        Vector2Subtract(hitbox.GetCenter(), player.hitbox.GetCenter()));

    TraceLog(LOG_INFO, "Move: %f %f", normVecToPlayer.x, normVecToPlayer.y);

    switch (type) {
    case MELEE:

        break;
    case RANGER:
        break;
    default:
        break;
    }
}

void Enemy::Draw() const { hitbox.DrawHitBox(sprite.color); }