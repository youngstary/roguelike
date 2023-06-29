#include <stdio.h>
#include "raylib.h"

class Map
{
public:
    Map();
    void Print();
    void Generate();

    int map[10][10] = {0};

    enum Dir
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    enum Room
    {
        NONE,
        NORMAL,
        ITEM,
        SHOP,
        BOSS
    };
};
