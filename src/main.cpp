#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

class Player
{
public:
    Vector2 position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    Vector2 acceleration = {(float)0.0f, (float)0.0f};

    float velocity = 4.0f;
    float dAcc = 0.1f;

    void Draw()
    {
        DrawCircle(position.x, position.y, 20, BLUE);
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

        /* Draw */
        BeginDrawing();

        ClearBackground(BLACK);

        DrawFPS(5, 5); // Show current FPS

        player.Draw();

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
