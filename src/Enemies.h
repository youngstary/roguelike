#include "Components.h"
#include <cstddef>
#include <raylib.h>

// Positive number means it's running away from the player
// Negative number means it's running towards the player
enum EnemyType { MELEE = -1, RANGER = 1 };

constexpr size_t numOfRays = 8;
struct Context {
    Vector2 rays[numOfRays];
    float interests[numOfRays];
    float dangers[numOfRays];
    void DrawRays(Vector2 center) const {
        for (size_t i = 0; i < numOfRays; i++) {
            Color color = (dangers[i] > 0.0f) ? RED : GREEN;
            DrawLine(center.x, center.y, center.x + rays[i].x * interests[i],
                     center.y + rays[i].y * interests[i], color);
        }
    }
};

struct Enemy {
    Enemy(float x, float y, EnemyType type);
    void Move(const float frameTime);
    void Draw() const;
    void Collision();
    // void CalcWeight(const HitBoxRect &target);
    // void ResetWeight();
    void AddToContext(const HitBoxRect &target);
    void PopulateContext();

    EnemyType type;
    HitBoxRect hitbox;
    Velocity vel;
    Vector2 movementWeight = {0};
    Context context;
    Health health;
    Sprite sprite;
};
