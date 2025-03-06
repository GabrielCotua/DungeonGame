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

void InitializeBaseMap()
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


int DrawMap(struct map map);
void PlayerSpawn(void);
int WhereIsPlayer(void);
int SpaceAvailable(int map[MAP_ROW][MAP_COL], enum MOVES moves);
int DrawPlayer(int x, int y, enum MOVES direction);
int PlayerMove(char move);

int main(void)
{
    InitializeBaseMap();
    DrawMap(base_map);
    PlayerSpawn();
    if (WhereIsPlayer() == 1) {
        printf("\nplayer found\n");
    }
    PlayerMove('w');
    printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
    DrawMap(base_map);
    while( (player_movement = getchar()) != EOF ) {
        if (PlayerMove(tolower(player_movement))) {
            DrawMap(base_map);
            
        }
    }

    return 0;
}

int DrawMap(struct map map)
{
    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {

            printf("%c ", map.map[row][col]);
        }
        printf("\n");
    }

    return 1;
}

// TODO: make player spawn in a random location of the map at the beginning
// only execute once.
void PlayerSpawn(void)
{
    srand(time(0));
    int rand_xAxis = (int) ( rand() % 9 ) + 1;
    int rand_yAxis = (int) ( rand() % 9 ) + 1;

    base_map.map[rand_xAxis][rand_yAxis] = '@';
}

// Looks for the player location in the map
int WhereIsPlayer(void)
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
int SpaceAvailable(int map[MAP_ROW][MAP_COL], enum MOVES moves)
{
    switch (moves)
    {
    case move_up:
        if (map[player.coords[xAxis] - 1][player.coords[yAxis]] == ' ')
        {
            printf("%d = %d is available\n", move_right, map[player.coords[xAxis] + 1][player.coords[yAxis] ]);
            player.coords[xAxis] = player.coords[xAxis] - 1;
        }
        return 1;

    case move_down:
        if (map[player.coords[xAxis] + 1][player.coords[yAxis]] == ' ')
        {
            printf("%d = %d is available\n", move_left, map[player.coords[xAxis] - 1][player.coords[yAxis]]);
            player.coords[xAxis] = player.coords[xAxis] + 1;
        }
        return 1;

    case move_right:
        if (map[player.coords[xAxis]][player.coords[yAxis] - 1] == ' ')
        {
            printf("%d = %d is available\n", move_up, map[player.coords[xAxis]][player.coords[yAxis] + 1]);
            player.coords[yAxis] = player.coords[yAxis] - 1;
        }
        return 1;

    case move_left:
        if (map[player.coords[xAxis]][player.coords[yAxis] + 1] == ' ')
        {
            printf("%d = %d is available\n", move_down, map[player.coords[xAxis]][player.coords[yAxis] - 1]);
            player.coords[yAxis] = player.coords[yAxis] + 1;
        }
        return 1;

    default:
        return 0;
    }
}

/*
@param move reads user input to where desires to move, takes a character
*/
int DrawPlayer(int x, int y, enum MOVES direction) {

    switch (tolower(direction))
    {
    case move_left:

        base_map.map[x][y-1] = ' ';
        base_map.map[x][y] = '@';

        return 1;

    case move_right:

        base_map.map[x][y+1] = ' ';
        base_map.map[x][y] = '@';

        return 1;

    case move_down:
    
    base_map.map[x-1][y] = ' ';
    base_map.map[x][y] = '@';

        return 1;

    case move_up:
    
    base_map.map[x+1][y] = ' ';
    base_map.map[x][y] = '@';

        return 1;

    default:
        return 0;
    }

}

int PlayerMove(char move)
{
    switch (tolower(move))
    {
    case 'w':
        if (SpaceAvailable(base_map.map, move_up))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_up);
        }

        return 1;

    case 'a':
        if (SpaceAvailable(base_map.map, move_right))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_right);
        }
        return 1;

    case 's':
        if (SpaceAvailable(base_map.map, move_down))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_down);
        }
        return 1;

    case 'd':
        if (SpaceAvailable(base_map.map, move_left))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_left);
        }
        return 1;

    default:

        return 0;
    }
}
