#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAP_COL 11
#define MAP_ROW 11
enum MOVES
{
    move_up,
    move_down,
    move_right,
    move_left
};

enum AXIS
{
    xAxis,
    yAxis
};

int layout_1[MAP_ROW][MAP_COL] = {

    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', '@', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}

};

struct map
{
    int map[MAP_ROW][MAP_COL];
};
struct map base_map;

void initializeBaseMap()
{
    memcpy(base_map.map, layout_1, sizeof(layout_1)); // Copy array contents
}
struct Player
{
    // first value coords[0] = {x coords} (horizontal)
    // second value coords[1] = {y coords} (vertical)
    int coords[2];
};
struct Player player;

int drawMap()
{
    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {

            printf("%c ", base_map.map[row][col]);
        }
        printf("\n");
    }

    return 1;
}
// TODO: make player spawn in a random location of the map at the beginning
void playerSpawn(void)
{
}
// Looks for the player location in the map
int whereIsPlayer(void)
{

    for (int row = 0; row < MAP_ROW; row++)
    {

        for (int col = 0; col < MAP_COL; col++)
        {

            if (base_map.map[row][col] == '@')
            {
                printf("\nLocation is coord-x %d, coord-y %d\n", row, col);
                player.coords[xAxis] = row;
                player.coords[yAxis] = col;
                return 1;
            }
        }
    }
    return 0;
}
/*
@param int map[MAP_ROW][MAP_COl] required to insert a map that uses the MAP_ROW and MAP_COL dimentions to avoid errors
@param enum MOVES moves is a enumerator to know where is the player heading to
*/
int spaceAvailable(int map[MAP_ROW][MAP_COL], enum MOVES moves)
{
    switch (moves)
    {
    case move_up:
        if (map[player.coords[xAxis]][player.coords[yAxis] + 1] == ' ')
        {
            printf("%d = %d is available", move_up, map[player.coords[0]][player.coords[1] + 1]);
        }
        return 1;

    case move_down:
        if (map[player.coords[xAxis]][player.coords[yAxis] - 1] == ' ')
        {
            printf("%d", move_down);
        }
        return 1;

    case move_right:
        if (map[player.coords[xAxis] + 1][player.coords[yAxis]] == ' ')
        {
            printf("%d", move_right);
        }
        return 1;

    case move_left:
        if (map[player.coords[xAxis] - 1][player.coords[yAxis]] == ' ')
        {
            printf("%d", move_left);
        }
        return 1;

    default:
        return 0;
    }
}

/*
@param move reads user input to where desires to move, takes a character
*/
int playerMove(char move)
{
    switch (tolower(move))
    {
    case 'w':
        if (spaceAvailable(base_map.map, move_up))
        {
            printf("\nsuccess");
        }

        return 1;

    case 'a':
        return 1;

    case 's':
        return 1;

    case 'd':
        return 1;

    default:
        return 0;
    }
}

int main(void)
{
    initializeBaseMap();
    drawMap(base_map, MAP_ROW, MAP_COL);
    whereIsPlayer();
    playerMove('w');
    printf("\n\nplayer x-cord = %d, player y-cord = %d", player.coords[xAxis], player.coords[yAxis]);

    return 0;
}