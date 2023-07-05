#include "Components.h"
#include <raylib.h>

// Positive number means it's running away from the player
// Negative number means it's running towards the player
enum EnemyType { MELEE = -1, RANGER = 1 };

struct Enemy {
    Enemy(float x, float y, EnemyType type);
    void Move(const float frameTime);
    void Draw() const;
    void Collision();
    void CalcWeight(const HitBoxRect &target);
    void ResetWeight();

    EnemyType type;
    HitBoxRect hitbox;
    Velocity vel;
    Vector2 movementWeight = {0};
    Health health;
    Sprite sprite;
};
