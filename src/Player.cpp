#include "Player.h"

#include "entt.hpp"
#include <cstdio>
#include <raylib.h>
#include <raymath.h>

entt::entity MakePlayer(entt::registry &reg, float x, float y) {
    float maxVelocity = 4.0f;
    float acc = 0.3f;
    float dAcc = 0.4f;

    const entt::entity player = reg.create();
    reg.emplace<Player>(player, Player{20.0f});
    reg.emplace<Position>(player, Position{x, y});
    reg.emplace<Velocity>(player, Velocity{{0}, maxVelocity, acc, dAcc});
    reg.emplace<Sprite>(player, Sprite{{0.0f, 0.0f, 32.0f, 32.0f}, RED});
    reg.emplace<CursorPos>(player, CursorPos{});
    reg.emplace<CameraFocus>(player);
    return player;
}

void UpdatePlayerVelocity(entt::registry &reg) {
    auto view = reg.view<Player, Velocity>();
    for (auto entity : view) {
        auto &vel = view.get<Velocity>(entity);
        // X-axis
        if (IsKeyDown(KEY_D)) {
            vel.current.x += vel.acc;
            if (vel.current.x > vel.max) {
                vel.current.x = vel.max;
            }
        } else if (IsKeyDown(KEY_A)) {
            vel.current.x -= vel.acc;
            if (vel.current.x < -vel.max) {
                vel.current.x = -vel.max;
            }
        } else {
            if (vel.current.x >= vel.dAcc) {
                vel.current.x -= vel.dAcc;
            } else if (vel.current.x <= -vel.dAcc) {
                vel.current.x += vel.dAcc;
            } else {
                vel.current.x = 0;
            }
        }

        // Y-axis
        if (IsKeyDown(KEY_W)) {
            vel.current.y -= vel.acc;
            if (vel.current.y < -vel.max) {
                vel.current.y = -vel.max;
            }
        } else if (IsKeyDown(KEY_S)) {
            vel.current.y += vel.acc;
            if (vel.current.y > vel.max) {
                vel.current.y = vel.max;
            }
        } else {
            if (vel.current.y >= vel.dAcc) {
                vel.current.y -= vel.dAcc;
            } else if (vel.current.y <= -vel.dAcc) {
                vel.current.y += vel.dAcc;
            } else {
                vel.current.y = 0;
            }
        }
    }
}

void UpdatePositions(entt::registry &reg) {
    auto view = reg.view<Position, Velocity>();
    for (auto entity : view) {
        auto &pos = view.get<Position>(entity).value;
        auto &vel = view.get<Velocity>(entity);

        pos.x += vel.current.x;
        pos.y += vel.current.y;
    }
}

void UpdatePointer(entt::registry &reg) {
    auto view = reg.view<Player, CursorPos, Position>();

    float centerX = GetScreenWidth() / 2.0f;
    float centerY = GetScreenHeight() / 2.0f;

    for (auto entity : view) {
        auto &margin = view.get<Player>(entity).cursorRadius;
        auto &pos = view.get<Position>(entity).value;
        auto &cursor = view.get<CursorPos>(entity);

        cursor.pos = GetMousePosition();

        float angle = Vector2Angle(cursor.pos, {centerX, centerY});

        float offsetX = (margin - cursor.radius) * cosf(angle);
        float offsetY = (margin - cursor.radius) * sinf(angle);

        cursor.pos.x = pos.x - offsetX;
        cursor.pos.y = pos.y - offsetY;
    }
}
