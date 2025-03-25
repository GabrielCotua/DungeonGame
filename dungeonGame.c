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
typedef struct Map
{
    int map[MAP_ROW][MAP_COL];
} maps ;

maps base_map = {
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

maps maze_map = {
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

typedef struct Player
{
    // first value coords[0] = {x coords} (horizontal)
    // second value coords[1] = {y coords} (vertical)
    int coords[2];
    char sprite;
} Player;

Player player = {
    .coords = {1,1},
    .sprite = '@'
};

typedef struct item 
{
    // first value coords[0] = {x coords} (horizontal)
    // second value coords[1] = {y coords} (vertical)   
    int corrds[2];
    enum ITEM_OPTIONS item_value;
    char sprite;
} Items;

Items money = {
    .item_value = item_point_plus,
    .sprite = '$'

};


int DrawMap( struct Map map);
int GetRandomCoords( int colRow);
void PlayerSpawn( struct Map * map, struct Player * player);
int WhereIsPlayer( struct Map map, struct Player * player);
int SpaceAvailable( struct Map * map, struct Player * player, enum MOVES moves);
int DrawPlayer(struct Map * map, struct Player * player);
int PlayerMove(char move, struct Map * map, struct Player * player);

int main(void)
{
    srand(time(0));
    char player_movement;
    int mapChosen;
    printf("What kind of map would you like to use?\
        \n0 - Base Map\
        \n1 - Maze Map\n");   
    scanf("%d", &mapChosen);
    switch (mapChosen)        
    {
        case(mapVer_base_map):
            PlayerSpawn(&base_map, &player);
            DrawMap(base_map);
            if (WhereIsPlayer(base_map, &player)) {
                printf("\nplayer found\n");
            }
            printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
            while( (player_movement = getchar()) != EOF ) {
                if (PlayerMove(tolower(player_movement), &base_map, &player)) {
                    DrawMap(base_map);
                    FLUSH;
                }
            }
            return 1;

        case(mapVer_maze_map):
            PlayerSpawn(&maze_map, &player);
            DrawMap(maze_map);
            if (WhereIsPlayer(maze_map, &player)) {
                printf("\nplayer found\n");
            }
            printf("\n\nplayer x-cord = %d, player y-cord = %d\n", player.coords[xAxis], player.coords[yAxis]);
            while( (player_movement = getchar()) != EOF ) {
                if (PlayerMove(tolower(player_movement), &maze_map, &player)) {
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

int DrawMap( struct Map map)
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
int GetRandomCoords(int colRow)
{
    return (int) ( rand() % colRow - 2 ) + 1;
}
void PlayerSpawn( struct Map * map, struct Player * player)
{
    int rand_xAxis = GetRandomCoords(MAP_ROW);
    int rand_yAxis = GetRandomCoords(MAP_COL);
    while ( map->map[rand_xAxis][rand_yAxis] == '*' ) {
        rand_xAxis = GetRandomCoords(MAP_ROW);
        rand_yAxis = GetRandomCoords(MAP_COL);
    }
    player->coords[0] = rand_xAxis;
    player->coords[1] = rand_yAxis;
    map->map[rand_xAxis][rand_yAxis] = player->sprite;

}

// Looks for the player location in the map
int WhereIsPlayer(struct Map map, struct Player * player)
{

    for (int row = 0; row < MAP_ROW; row++)
    {

        for (int col = 0; col < MAP_COL; col++)
        {

            if (map.map[row][col] == player->sprite)
            {
                printf("\nLocation is coord-x %d, coord-y %d\n", row, col);
                player->coords[xAxis] = row;
                player->coords[yAxis] = col;
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
int SpaceAvailable(struct Map * map, struct Player * player, enum MOVES move)
{
    int x = player->coords[xAxis];
    int y = player->coords[yAxis];

    switch (move)
    {
    case move_up:
        if (map->map[x - 1][y] == ' ')
        {
            player->coords[xAxis]--;
            return 1;
        }
        break;
    case move_down:
        if (map->map[x + 1][y] == ' ')
        {
            player->coords[xAxis]++;
            return 1;
        }
        break;
    case move_right:
        if (map->map[x][y + 1] == ' ')
        {
            player->coords[yAxis]++;
            return 1;
        }
        break;
    case move_left:
        if (map->map[x][y - 1] == ' ')
        {
            player->coords[yAxis]--;
            return 1;
        }
        break;
    }
    return 0;
}

/*
@param move reads user input to where desires to move, takes a character
*/
int DrawPlayer(struct Map * map, struct Player * player)
{
    int x = player->coords[xAxis];
    int y = player->coords[yAxis];

    // Limpiar la posición anterior
    for (int i = 0; i < MAP_ROW; i++) {
        for (int j = 0; j < MAP_COL; j++) {
            if (map->map[i][j] == player->sprite) {
                map->map[i][j] = ' ';
            }
        }
    }

    // Dibujar al jugador en la nueva posición
    map->map[x][y] = player->sprite;

    return 1;
}


int PlayerMove(char move, struct Map * map, struct Player * player)
{
    enum MOVES direction;

    switch (tolower(move))
    {
    case 'w':       
        direction = move_up; 
        break;
        
    case 's':       
        direction = move_down; 
        break;
        
    case 'a':       
        direction = move_left; 
        break;
        
    case 'd':       
        direction = move_right; 
        break;
        
    default:        
        return 0;
    }

    if (SpaceAvailable(map, player, direction))
    {
        DrawPlayer(map, player);
        return 1;
    }
    
    return 0;
}
