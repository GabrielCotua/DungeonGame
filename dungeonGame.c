#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define FLUSH while (getchar() != '\n')
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
    yAxis,
    xAxis
};

enum MAP_VERSION 
{
    mapVer_base_map,
    mapVer_maze_map
};

enum ITEM_OPTIONS
{
    item_point_plus,
    item_point_minus
};
struct map
{
    int map[MAP_ROW][MAP_COL];
};

struct map base_map = {
    .map = {
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
    }
};

struct map maze_map = {
    .map = {
        {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', ' ', ' ', ' ', '*'},
        {'*', ' ', ' ', ' ', ' ', ' ', ' ', '*', '*', ' ', '*'},
        {'*', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
        {'*', ' ', ' ', '*', ' ', ' ', ' ', '*', '*', '*', '*'},
        {'*', ' ', ' ', '*', ' ', ' ', ' ', '*', ' ', ' ', '*'},
        {'*', ' ', '*', '*', '*', '*', ' ', '*', '*', ' ', '*'},
        {'*', ' ', '*', ' ', ' ', '*', '*', '*', '*', ' ', '*'},
        {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
    }
};

struct Player
{
    // first value coords[0] = {x coords} (horizontal)
    // second value coords[1] = {y coords} (vertical)
    int coords[2];
    char sprite;
};
struct Player player = {
    .sprite = '@'
};

struct item 
{
    // first value coords[0] = {x coords} (horizontal)
    // second value coords[1] = {y coords} (vertical)   
    int corrds[2];
    enum ITEM_OPTIONS item_value;
    char sprite;
};

struct item money = {
    .corrds = {1,1},
    .item_value = item_point_plus,
    .sprite = '$'

};


int DrawMap(struct map map);
void PlayerSpawn(struct map * map, struct Player player);
int WhereIsPlayer(struct map map, struct Player player);
int SpaceAvailable(struct map * map, enum MOVES moves);
int DrawPlayer(int x, int y, enum MOVES direction, struct map * map);
int PlayerMove(char move, struct map * map);

int main(void)
{
    char player_movement;
    int mapChosen;
    printf("What kind of map would you like to use?\
        \n0 - Base Map\
        \n1 - Maze Map\n");   
    scanf("%d", &mapChosen);
    switch (mapChosen)        
    {
        case(mapVer_base_map):
            PlayerSpawn(&base_map);
            DrawMap(base_map);
            if (WhereIsPlayer(base_map)) {
                printf("\nplayer found\n");
            }
            printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
            while( (player_movement = getchar()) != EOF ) {
                if (PlayerMove(tolower(player_movement), &base_map)) {
                    DrawMap(base_map);
                    FLUSH;
                }
            }
            return 1;

        case(mapVer_maze_map):
            PlayerSpawn(&maze_map);
            DrawMap(maze_map);
            if (WhereIsPlayer(maze_map)) {
                printf("\nplayer found\n");
            }
            printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
            while( (player_movement = getchar()) != EOF ) {
                if (PlayerMove(tolower(player_movement), &maze_map)) {
                    DrawMap(maze_map);
                    FLUSH;
                }
            }
            return 1;

        default:
        printf("not a valid option");
        return 0;
    }
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
int GetRandomCoords(int colRow )
{
    srand(time(0));
    return (int) ( rand() % colRow - 2 ) + 1;
}
void PlayerSpawn(struct map * map, struct Player player)
{
    int rand_xAxis = GetRandomCoords(MAP_ROW);
    int rand_yAxis = GetRandomCoords(MAP_COL);
    while ( map->map[rand_xAxis][rand_yAxis] == '*' ) {
        rand_xAxis = GetRandomCoords(MAP_ROW);
        rand_yAxis = GetRandomCoords(MAP_COL);
    }
    map->map[rand_xAxis][rand_yAxis] = player.sprite;

}

// Looks for the player location in the map
int WhereIsPlayer(struct map map, struct Player player)
{

    for (int row = 0; row < MAP_ROW; row++)
    {

        for (int col = 0; col < MAP_COL; col++)
        {

            if (map.map[row][col] == player.sprite)
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

int SpaceAvailable(struct map * map, enum MOVES moves)
 {
     switch (moves)
     {
     case move_up:
         if (map->map[player.coords[xAxis] - 1][player.coords[yAxis]] == ' ')
         {
             printf("%d = %d is available\n", move_right, map->map[player.coords[xAxis] + 1][player.coords[yAxis] ]);
             player.coords[xAxis] = player.coords[xAxis] - 1;
         }
         return 1;
 
     case move_down:
         if (map->map[player.coords[xAxis] + 1][player.coords[yAxis]] == ' ')
         {
             printf("%d = %d is available\n", move_left, map->map[player.coords[xAxis] - 1][player.coords[yAxis]]);
             player.coords[xAxis] = player.coords[xAxis] + 1;
         }
         return 1;
 
     case move_right:
         if (map->map[player.coords[xAxis]][player.coords[yAxis] - 1] == ' ')
         {
             printf("%d = %d is available\n", move_up, map->map[player.coords[xAxis]][player.coords[yAxis] + 1]);
             player.coords[yAxis] = player.coords[yAxis] - 1;
         }
         return 1;
 
     case move_left:
         if (map->map[player.coords[xAxis]][player.coords[yAxis] + 1] == ' ')
         {
             printf("%d = %d is available\n", move_down, map->map[player.coords[xAxis]][player.coords[yAxis] - 1]);
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

int DrawPlayer(int x, int y, enum MOVES direction, struct map * map, struct Player player) {

    switch (tolower(direction))
    {
    case move_left:

        map->map[x][y-1] = ' ';
        map->map[x][y] = player.sprite;

        return 1;

    case move_right:

        map->map[x][y+1] = ' ';
        map->map[x][y] = '@';

        return 1;

    case move_down:
    
        map->map[x-1][y] = ' ';
        map->map[x][y] = '@';

        return 1;

    case move_up:
    
        map->map[x+1][y] = ' ';
        map->map[x][y] = '@';

        return 1;

    default:
        return 0;
    }

}

int PlayerMove(char move, struct map * map)
{
    switch (tolower(move))
    {
    case 'w':
        if (SpaceAvailable(map, move_up))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_up, map);
        }

        return 1;

    case 'a':
        if (SpaceAvailable(map, move_right))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_right, map);
        }
        return 1;

    case 's':
        if (SpaceAvailable(map, move_down))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_down, map);
        }
        return 1;

    case 'd':
        if (SpaceAvailable(map, move_left))
        {
            DrawPlayer(player.coords[xAxis], player.coords[yAxis], move_left, map);
        }
        return 1;

    default:

        return 0;
    }
}
