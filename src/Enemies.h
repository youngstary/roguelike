#include "Components.h"

enum EnemyType { MELEE, RANGER };

struct Enemy {
    Enemy(float x, float y, EnemyType type);
    void Move(const Player &player);
    void Draw() const;
    void Collision();

    EnemyType type;
    HitBoxRect hitbox;
    Velocity vel;
    Health health;

    Sprite sprite;
};
