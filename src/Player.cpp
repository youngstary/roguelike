#include "Player.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

Player::Player(float x, float y) { pos = {x, y}; }

void Player::Move() {
    // X-axis
    if (IsKeyDown(KEY_D)) {
        vel.x += acc;
        if (vel.x > maxVelocity) {
            vel.x = maxVelocity;
        }
    } else if (IsKeyDown(KEY_A)) {
        vel.x -= acc;
        if (vel.x < -maxVelocity) {
            vel.x = -maxVelocity;
        }
    } else {
        if (vel.x >= dAcc) {
            vel.x -= dAcc;
        } else if (vel.x <= -dAcc) {
            vel.x += dAcc;
        } else {
            vel.x = 0;
        }
    }

    // Y-axis
    if (IsKeyDown(KEY_W)) {
        vel.y -= acc;
        if (vel.y < -maxVelocity) {
            vel.y = -maxVelocity;
        }
    } else if (IsKeyDown(KEY_S)) {
        vel.y += acc;
        if (vel.y > maxVelocity) {
            vel.y = maxVelocity;
        }
    } else {
        if (vel.y >= dAcc) {
            vel.y -= dAcc;
        } else if (vel.y <= -dAcc) {
            vel.y += dAcc;
        } else {
            vel.y = 0;
        }
    }

    pos.x += vel.x;
    pos.y += vel.y;
}

void Player::UpdatePointer(Camera2D *camera) {
    ptrPos = GetMousePosition();

    float centerX = GetScreenWidth() / 2.0f;
    float centerY = GetScreenHeight() / 2.0f;

    angle = Vector2Angle(ptrPos, {centerX, centerY});

    float offsetX = (borderRadius - ptrRadius) * cosf(angle);
    float offsetY = (borderRadius - ptrRadius) * sinf(angle);

    ptrPos.x = pos.x - offsetX;
    ptrPos.y = pos.y - offsetY;
}

void Player::Draw() {
    DrawCircleV(pos, borderRadius, BLANK);
    DrawCircleV(pos, radius, BLUE);
    DrawCircleV(ptrPos, ptrRadius, RED);
}
