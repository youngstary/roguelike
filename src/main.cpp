#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <math.h>

class Player {
public:
  Vector2 position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  Vector2 velocity = {0.0f, 0.0f};
  Vector2 ptrPos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  float maxVelocity = 4.0f;
  float acc = 0.3f;
  float dAcc = 0.4f;

  float radius = 20;
  float ptrRadius = 10;
  float borderRadius = 45;

  float angle = 0.0f;
  float dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;

  void Draw() {
    DrawCircleV(position, borderRadius, BLANK);
    DrawCircleV(position, radius, BLUE);
    DrawCircleV(ptrPos, ptrRadius, RED);
  }

  void MovePointer() {
    if (!CheckCollisionPointCircle(ptrPos, position, borderRadius - 20)) {
      dx = ptrPos.x - position.x;
      dy = ptrPos.y - position.y;

      angle = atan2f(dy, dx);

      dxx = (borderRadius - ptrRadius) * cosf(angle);
      dyy = (borderRadius - ptrRadius) * sinf(angle);

      ptrPos.x = position.x + dxx;
      ptrPos.y = position.y + dyy;
    }
  }

  void Move() {
    // X-axis
    if (IsKeyDown(KEY_D)) {
        velocity.x += acc;
      if (velocity.x > maxVelocity) {
        velocity.x = maxVelocity;
      }
    } else if (IsKeyDown(KEY_A)) {
        velocity.x -= acc;
      if (velocity.x < -maxVelocity) {
        velocity.x = -maxVelocity;
      }
    } else {
      if (velocity.x >= dAcc) {
        velocity.x -= dAcc;
      } else if (velocity.x <= -dAcc) {
        velocity.x += dAcc;
      } else {
        velocity.x = 0;
      }
    }
  

    // Y-axis
    if (IsKeyDown(KEY_W)) {
        velocity.y -= acc;
      if (velocity.y < -maxVelocity) {
        velocity.y = -maxVelocity;
      }
    } else if (IsKeyDown(KEY_S)) {
      velocity.y += acc;
      if (velocity.y > maxVelocity) {
        velocity.y = maxVelocity;
      }
    } else {
      if (velocity.y >= dAcc) {
        velocity.y -= dAcc;
      } else if (velocity.y <= -dAcc) {
        velocity.y += dAcc;
      } else {
        velocity.y = 0;
      }
    }

    // if (IsKeyUp(KEY_D)) {
    //   if (velocity.x >= 0.0f) {
    //     velocity.x -= dAcc;
    //     if (velocity.x <= 0.1f && velocity.x >= -0.1f)
    //       velocity.x = 0.0f;
    //   }
    // }
    // if (IsKeyUp(KEY_A)) {
    //   if (velocity.x <= 0.0f) {
    //     velocity.x += dAcc;
    //     if (velocity.x <= 0.1f && velocity.x >= -0.1f)
    //       velocity.x = 0.0f;
    //   }
    // }
    // if (IsKeyUp(KEY_W)) {
    //   if (velocity.y <= 0.0f) {
    //     velocity.y += dAcc;
    //     if (velocity.y <= 0.1f && velocity.y >= -0.1f)
    //       velocity.y = 0.0f;
    //   }
    // }
    // if (IsKeyUp(KEY_S)) {
    //   if (velocity.y >= 0.0f) {
    //     velocity.y -= dAcc;
    //     if (velocity.y <= 0.1f && velocity.y >= -0.1f)
    //       velocity.y = 0.0f;
    //   }
    // }

    position.x += velocity.x;
    position.y += velocity.y;
  }
};

int main() {
  const int screenWidth = 1024;
  const int screenHeight = 768;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  GuiLoadStyleDefault();

  Player player;

  /* Main game loop */
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    /* Update */
    player.Move();
    player.ptrPos = GetMousePosition();
    player.MovePointer();
    /* Draw */
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawFPS(10, 10); // Show current FPS

    player.Draw();

    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
