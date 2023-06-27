#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <math.h>

class Player
{
public:
    Vector2 position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    Vector2 acceleration = {(float)0.0f, (float)0.0f};
    Vector2 ptrPos = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};

    float velocity = 4.0f;
    float dAcc = 0.1f;

    float radius = 20;
    float ptrRadius = 10;
    float borderRadius = 45;

    float angle = 0.0f;
    float dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;

    void Draw()
    {
        DrawCircleV(position, borderRadius, BLANK);
        DrawCircleV(position, radius, BLUE);
        DrawCircleV(ptrPos, ptrRadius, RED);
    }

    void MovePointer()
    {
        if (!CheckCollisionPointCircle(ptrPos, position, borderRadius - 20))
        {
            dx = ptrPos.x - position.x;
            dy = ptrPos.y - position.y;

            angle = atan2f(dy, dx);

            dxx = (borderRadius - ptrRadius) * cosf(angle);
            dyy = (borderRadius - ptrRadius) * sinf(angle);

            ptrPos.x = position.x + dxx;
            ptrPos.y = position.y + dyy;
        }
    }

    void Move()
    {
        if (IsKeyDown(KEY_D))
        {
            if (acceleration.x <= 1.0f)
                acceleration.x += dAcc;
        }
        if (IsKeyDown(KEY_A))
        {
            if (acceleration.x >= -1.0f)
                acceleration.x -= dAcc;
        }
        if (IsKeyDown(KEY_W))
        {
            if (acceleration.y >= -1.0f)
                acceleration.y -= dAcc;
        }
        if (IsKeyDown(KEY_S))
        {
            if (acceleration.y <= 1.0f)
                acceleration.y += dAcc;
        }

        if (IsKeyUp(KEY_D))
        {
            if (acceleration.x >= 0.0f)
            {
                acceleration.x -= dAcc;
                if (acceleration.x <= 0.1f && acceleration.x >= -0.1f)
                    acceleration.x = 0.0f;
            }
        }
        if (IsKeyUp(KEY_A))
        {
            if (acceleration.x <= 0.0f)
            {
                acceleration.x += dAcc;
                if (acceleration.x <= 0.1f && acceleration.x >= -0.1f)
                    acceleration.x = 0.0f;
            }
        }
        if (IsKeyUp(KEY_W))
        {
            if (acceleration.y <= 0.0f)
            {
                acceleration.y += dAcc;
                if (acceleration.y <= 0.1f && acceleration.y >= -0.1f)
                    acceleration.y = 0.0f;
            }
        }
        if (IsKeyUp(KEY_S))
        {
            if (acceleration.y >= 0.0f)
            {
                acceleration.y -= dAcc;
                if (acceleration.y <= 0.1f && acceleration.y >= -0.1f)
                    acceleration.y = 0.0f;
            }
        }

        position.x += velocity * acceleration.x;
        position.y += velocity * acceleration.y;
    }
};

int main()
{
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
