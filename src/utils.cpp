#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include "raylib.h"

#include "utils.h"

Map::Map()
{
}

void Map::Print()
{
    printf("---ARRAY---\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("-----------\n");
}

void Map::Generate()
{
    std::memset(map, 0, (10 * 10) * (sizeof *map));
    const int level = 1;

    int x = GetRandomValue(2, 7);
    int y = GetRandomValue(2, 7);

    int bossX, bossY, dx, dy;

    do
    {
        bossX = GetRandomValue(0, 9);
        bossY = GetRandomValue(0, 9);
        dx = abs(bossX - x);
        dy = abs(bossY - y);
    } while (!(dx <= 3 + level && dx >= 3 && dy <= 3 + level && dy >= 3));

    map[y][x] = NORMAL;
    map[bossY][bossX] = BOSS;

    int horizontal = dx;
    int vertical = dy - 1; // One vertical move counts also as horizontal move
    const int moves = horizontal + vertical;
    int sequence[moves];

    for (int i = 0; i < moves; i++)
    {
        int choice;

        if (horizontal == 0)
            choice = VERTICAL;
        else if (vertical == 0)
            choice = HORIZONTAL;
        else
            choice = GetRandomValue(HORIZONTAL, VERTICAL);

        if (choice == HORIZONTAL)
        {
            if (x < bossX)
                sequence[i] = RIGHT;
            else
                sequence[i] = LEFT;
            horizontal--;
        }
        else if (choice == VERTICAL)
        {
            if (y < bossY)
                sequence[i] = DOWN;
            else
                sequence[i] = UP;
            vertical--;
        }
    }

    for (int move : sequence)
    {
        if (move == UP)
            y--;
        else if (move == RIGHT)
            x++;
        else if (move == DOWN)
            y++;
        else if (move == LEFT)
            x--;
        map[y][x] = NORMAL;
    }
}
