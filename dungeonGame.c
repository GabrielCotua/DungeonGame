#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define COL 11
#define ROW 11
enum MOVES {move_up, move_down, move_right, move_left};

int base_map[ROW][COL] = {

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

struct Player
{
    int coord_x;
    int coord_y;
};

struct Player player;

int drawMap()
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {

            printf("%c ", base_map[row][col]);
        }
        printf("\n");
    }

    return 1;
}
int playerSpawn(void) {

}

int whereIsPlayer(void)
{

    int coord_x = -1;
    int coord_y = -1;
    for (int row = 0; row < ROW; row++)
    {

        for (int col = 0; col < COL; col++)
        {

            if (base_map[row][col] == '@')
            {
                printf("\nLocation is coord-x %d, coord-y %d\n", row, col);
                player.coord_x = row;
                player.coord_y = col;
                return 1;
            }
        }
    }
    return 0;
}
int spaceAvailable(int map[ROW][COL], enum MOVES moves)
{
    switch(moves) {
        case move_up:
            if(map[player.coord_x][player.coord_y + 1] == ' '){
                printf("%d = %d is available", move_up, map[player.coord_x][player.coord_y + 1]);
        }
        return 1;

        case move_down:
            if(map[player.coord_x][player.coord_y - 1] == ' '){
                printf("%d", move_down);
            }
        return 1;
        
        case move_right:
        if(map[player.coord_x + 1][player.coord_y] == ' '){
            printf("%d", move_right);
        }
        return 1;
        
        case move_left:
        if(map[player.coord_x - 1][player.coord_y] == ' '){
            printf("%d", move_left);
        }
        return 1;

        default:
        return 0;
    }
}
int playerMove(char move) {
    switch(tolower(move)) {
        case 'w':
            if (spaceAvailable(base_map, move_up)) {
                printf("\nsuccess");
            }
        
            break;

        case 'a':
            break;

        case 's':
            break;

        case 'd':
            break;

        default:
            break;
    }
}



int main(void)
{

    drawMap(base_map, ROW, COL);
    whereIsPlayer();
    playerMove('w');
    printf("\n\n player x-cord = %d, player y-cord = %d", player.coord_x, player.coord_y);

    return 0;
}