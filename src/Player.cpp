#include "Player.h"
#include "Components.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

Player::Player(float x, float y) : hitbox({x, y, 32, 32}) {
    cursor.radius = 15.0f;
}

void Player::Move(const float frameTime) {
    // X-axis
    if (IsKeyDown(KEY_D)) {
        vel.x += vel.acc;
        if (vel.x > vel.max) {
            vel.x = vel.max;
        }
    } else if (IsKeyDown(KEY_A)) {
        vel.x -= vel.acc;
        if (vel.x < -vel.max) {
            vel.x = -vel.max;
        }
    } else {
        if (vel.x >= vel.dAcc) {
            vel.x -= vel.dAcc;
        } else if (vel.x <= -vel.dAcc) {
            vel.x += vel.dAcc;
        } else {
            vel.x = 0;
        }
    }

    // Y-axis
    if (IsKeyDown(KEY_W)) {
        vel.y -= vel.acc;
        if (vel.y < -vel.max) {
            vel.y = -vel.max;
        }
    } else if (IsKeyDown(KEY_S)) {
        vel.y += vel.acc;
        if (vel.y > vel.max) {
            vel.y = vel.max;
        }
    } else {
        if (vel.y >= vel.dAcc) {
            vel.y -= vel.dAcc;
        } else if (vel.y <= -vel.dAcc) {
            vel.y += vel.dAcc;
        } else {
            vel.y = 0;
        }
    }

    lastPosX = hitbox.x;
    hitbox.x += vel.x * frameTime;
    hitbox.y += vel.y * frameTime;
}

void Player::UpdatePointer(Camera2D *camera) {
    Vector2 mousePos = GetMousePosition();

    float margin =
        sqrtf(hitbox.width * hitbox.width + hitbox.height * hitbox.height);

    float angle = Vector2Angle(
        mousePos, {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});

    float offsetX = (margin - cursor.radius) * cosf(angle);
    float offsetY = (margin - cursor.radius) * sinf(angle);

    Vector2 playerCenter = hitbox.GetCenter();

    cursor.x = playerCenter.x - offsetX;
    cursor.y = playerCenter.y - offsetY;
}

void Player::Draw() const {
    // Draw hitbox
    hitbox.DrawHitBox(BLUE);

    // Draw cursor
    cursor.DrawHitBox(RED);
}

void Player::Collision(EntityType type, HitBoxRect collisionHitbox) {
    switch (type) {
    case WALL:
        // Check the direction of the collision
        if (CheckCollisionRecs(
                {lastPosX, hitbox.y, hitbox.width, hitbox.height},
                collisionHitbox)) {
            // Player's bottom
            if (vel.y > 0) {
                hitbox.y = collisionHitbox.y - hitbox.height;
            } else { // Player's top
                hitbox.y = collisionHitbox.y + collisionHitbox.height;
            }
            // Collision in Y axis
            vel.y = 0;
        } else {
            // Player's right
            if (vel.x > 0) {
                hitbox.x = collisionHitbox.x - hitbox.width;
            } else { // Player's left
                hitbox.x = collisionHitbox.x + collisionHitbox.width;
            }
            // Collision in X axis
            vel.x = 0;
        }
        break;
    default:
        break;
    }
}