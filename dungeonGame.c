#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAP_COL 11
#define MAP_ROW 11
char player_movement;
enum MOVES
{
    move_up,
    move_down,
    move_right,
    move_left
};

enum AXIS
{
    yAxis,
    xAxis
};

int layout_1[MAP_ROW][MAP_COL] = {

    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
    {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
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
// only execute once.
void playerSpawn(void)
{
    srand(time(0));
    int rand_xAxis = (int) ( rand() % 9 ) + 1;
    int rand_yAxis = (int) ( rand() % 9 ) + 1;

    base_map.map[rand_xAxis][rand_yAxis] = '@';
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
            printf("%d = %d is available\n", move_up, map[player.coords[xAxis]][player.coords[yAxis] + 1]);
            player.coords[yAxis] = player.coords[yAxis] + 1;
        }
        return 1;

    case move_down:
        if (map[player.coords[xAxis]][player.coords[yAxis] - 1] == ' ')
        {
            printf("%d = %d is available\n", move_down, map[player.coords[xAxis]][player.coords[yAxis] + 1]);
            player.coords[yAxis] = player.coords[yAxis] - 1;
        }
        return 1;

    case move_right:
        if (map[player.coords[xAxis] + 1][player.coords[yAxis]] == ' ')
        {
            printf("%d = %d is available\n", move_right, map[player.coords[xAxis]][player.coords[yAxis] + 1]);
            player.coords[xAxis] = player.coords[xAxis] + 1;
        }
        return 1;

    case move_left:
        if (map[player.coords[xAxis] - 1][player.coords[yAxis]] == ' ')
        {
            printf("%d = %d is available\n", move_left, map[player.coords[xAxis]][player.coords[yAxis] + 1]);
            player.coords[xAxis] = player.coords[xAxis] - 1;

        }
        return 1;

    default:
        return 0;
    }
}

/*
@param move reads user input to where desires to move, takes a character
*/
int drawPlayer(int x, int y, enum MOVES direction) {

    switch (tolower(direction))
    {
    case move_up:

        base_map.map[x][y-1] = ' ';
        base_map.map[x][y] = '@';

        return 1;

    case move_down:

        base_map.map[x][y+1] = ' ';
        base_map.map[x][y] = '@';

        return 1;

    case move_right:
    
    base_map.map[x-1][y] = ' ';
    base_map.map[x][y] = '@';

        return 1;

    case move_left:
    
    base_map.map[x+1][y] = ' ';
    base_map.map[x][y] = '@';

        return 1;

    default:
        return 0;
    }

}

int playerMove(char move)
{
    switch (tolower(move))
    {
    case 'w':
        if (spaceAvailable(base_map.map, move_up))
        {
            drawPlayer(player.coords[xAxis], player.coords[yAxis], move_up);
        }

        return 1;

    case 'a':
        if (spaceAvailable(base_map.map, move_right))
        {
            drawPlayer(player.coords[xAxis], player.coords[yAxis], move_right);
        }
        return 1;

    case 's':
        if (spaceAvailable(base_map.map, move_down))
        {
            drawPlayer(player.coords[xAxis], player.coords[yAxis], move_down);
        }
        return 1;

    case 'd':
        if (spaceAvailable(base_map.map, move_left))
        {
            drawPlayer(player.coords[xAxis], player.coords[yAxis], move_left);
        }
        return 1;

    default:

        return 0;
    }
}

int main(void)
{
    initializeBaseMap();
    drawMap(base_map, MAP_ROW, MAP_COL);
    playerSpawn();
    if (whereIsPlayer() == 1) {
        printf("\nplayer found\n");
    }
    playerMove('w');
    printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
    drawMap(base_map, MAP_ROW, MAP_COL);
    while(scanf("%c", &player_movement)) {
        if (playerMove(tolower(player_movement))) {
            drawMap(base_map, MAP_ROW, MAP_COL);
            
        }
    }

    return 0;
}