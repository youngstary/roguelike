#include "Player.h"
#include "Components.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

Player::Player(float x, float y)
    : hitbox({x, y, 32, 32}),
      vel(Velocity{
          .current = 0.0f, .max = 250.0f, .acc = 70.0f, .dAcc = 80.0f}),
      health({5}), cursor({15.0f}) {}

void Player::Move(const float frameTime) {
    // X-axis
    float x = 0.0f;
    if (IsKeyDown(KEY_D)) {
        x = 1.0f;
    } else if (IsKeyDown(KEY_A)) {
        x = -1.0f;
    }

    // Y-axis
    float y = 0.0f;
    if (IsKeyDown(KEY_W)) {
        y = -1.0f;
    } else if (IsKeyDown(KEY_S)) {
        y = 1.0f;
    }

    if (x == 0.0f && y == 0.0f) {
        vel.current -= vel.dAcc;
        if (vel.current < 0.0f) {
            vel.current = 0.0f;
        }
    } else {
        vel.UpdateAngle({x, y});

        vel.current += vel.acc;
        if (vel.current > vel.max) {
            vel.current = vel.max;
        }
    }

    Vector2 moveVector = Vector2Rotate(Vector2{0.0f, -vel.current}, vel.angle);
    vel.x = moveVector.x;
    vel.y = moveVector.y;

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
    vel.DrawVectorLine(hitbox.x, hitbox.y);

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