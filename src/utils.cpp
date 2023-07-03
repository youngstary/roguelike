#include "raylib.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <vector>

#include "utils.h"

Map::Map() {}

void Map::Print() {
    printf("---ARRAY---\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("-----------\n");
}

void Map::Generate() {
    std::memset(map, 0, (10 * 10) * (sizeof(int)));
    const int level = 1;

    int x = GetRandomValue(2, 7);
    int y = GetRandomValue(2, 7);

    int bossX, bossY, dx, dy;

    do {
        bossX = GetRandomValue(0, 9);
        bossY = GetRandomValue(0, 9);
        dx = abs(bossX - x);
        dy = abs(bossY - y);
    } while (!(dx <= 3 + level && dx >= 3 && dy <= 3 + level && dy >= 3));

    map[y][x] = NORMAL;
    map[bossY][bossX] = BOSS;

    int horizontal = dx;
    int vertical = dy - 1; // One vertical move counts also as horizontal move
    int moves = horizontal + vertical;
    std::vector<int> sequence(moves);

    for (int i = 0; i < moves; i++) {
        int choice;

        if (horizontal == 0)
            choice = VERTICAL;
        else if (vertical == 0)
            choice = HORIZONTAL;
        else
            choice = GetRandomValue(HORIZONTAL, VERTICAL);

        if (choice == HORIZONTAL) {
            if (x < bossX)
                sequence[i] = RIGHT;
            else
                sequence[i] = LEFT;
            horizontal--;
        } else if (choice == VERTICAL) {
            if (y < bossY)
                sequence[i] = DOWN;
            else
                sequence[i] = UP;
            vertical--;
        }
    }

    bool canCreateItemRoom = true;
    bool canCreateShop = true;
    int createItemRoom;
    int createShop;

    for (int move : sequence) {
        if (move == UP)
            y--;
        else if (move == RIGHT)
            x++;
        else if (move == DOWN)
            y++;
        else if (move == LEFT)
            x--;

        map[y][x] = NORMAL;

        if (canCreateItemRoom)
            createItemRoom = GetRandomValue(1, moves);

        if (canCreateShop)
            createShop = GetRandomValue(1, moves);

        if (createItemRoom == 1) {
            MoveRandomDirection(x, y, ITEM);
            canCreateItemRoom = false;
            createItemRoom = -1;
        }

        if (createShop == 1) {
            MoveRandomDirection(x, y, SHOP);
            canCreateShop = false;
            createShop = -1;
        }

        moves--;
    }

    Map::Print();
}

int Map::GetRandomDirection(int x, int y) {
    while (true) {
        int dir = GetRandomValue(UP, LEFT);

        if (dir == UP && y != 0 && map[y - 1][x] == 0)
            return UP;
        else if (dir == RIGHT && x < 9 && map[y][x + 1] == 0) // Indeks od 0 do 9, a nie 10
            return RIGHT;
        else if (dir == DOWN && y < 9 && map[y + 1][x] == 0) // Indeks od 0 do 9, a nie 10
            return DOWN;
        else if (dir == LEFT && x > 0 && map[y][x - 1] == 0)  // Indeks od 0, a nie -1
            return LEFT;
    }
}

void Map::MoveRandomDirection(int x, int y, int room) {
    int dir = Map::GetRandomDirection(x, y);

    if (dir == UP)
        map[y - 1][x] = room;
    else if (dir == RIGHT)
        map[y][x + 1] = room;
    else if (dir == DOWN)
        map[y + 1][x] = room;
    else if (dir == LEFT)
        map[y][x - 1] = room;
}