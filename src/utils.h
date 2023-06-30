#include "raylib.h"
#include <stdio.h>

class Map {
  public:
    Map();
    void Print();
    void Generate();
    int GetRandomDirection(int x, int y);
    void MoveRandomDirection(int x, int y, int room);
    int map[10][10] = {0};

    enum Dir { UP, RIGHT, DOWN, LEFT, HORIZONTAL, VERTICAL };

    enum Room { NONE, NORMAL, ITEM, SHOP, BOSS };
};
