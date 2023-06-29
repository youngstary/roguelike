#include <stdio.h>
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
    const int level = 4;
    const int rooms = 5 + GetRandomValue(1, 3) + level * 2;
    int x = 5;
    int y = 5;
    Room room = NORMAL;
    Dir dir;

    for (int i = 0; i < rooms; i++)
    {
        map[y][x] = room;
        while (true)
        {
            dir = Dir(GetRandomValue(0, 3));
            if (dir == UP && y != 0 && map[y - 1][x] == 0)
            {
                y--;
                break;
            }
            else if (dir == RIGHT && x != 10 && map[y][x + 1] == 0)
            {
                x++;
                break;
            }
            else if (dir == DOWN && y != 10 && map[y + 1][x] == 0)
            {
                y++;
                break;
            }
            else if (dir == LEFT && x != 0 && map[y][x - 1] == 0)
            {
                x--;
                break;
            }
        }
    }
}