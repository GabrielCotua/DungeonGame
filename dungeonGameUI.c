#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAP_COL 11
#define MAP_ROW 11

enum MOVES { move_up, move_down, move_right, move_left };
enum AXIS { yAxis, xAxis };
enum MAP_VERSION { mapVer_base_map, mapVer_maze_map };

typedef struct Map {
    int map[MAP_ROW][MAP_COL];
} maps;

maps base_map = { .map = {
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
} };

typedef struct Player {
    int coords[2];
    char sprite;
} Player;

Player player = { .coords = {1,1}, .sprite = '@' };

void DrawMap(maps *map);
void PlayerSpawn(maps *map, Player *player);
void DrawPlayer(maps *map, Player *player);
void PlayerMove(int move, maps *map, Player *player);

int main(void) {
    srand(time(0));
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    PlayerSpawn(&base_map, &player);
    while (1) {
        clear();
        DrawMap(&base_map);
        refresh();

        int ch = getch();
        if (ch == 'q') break;

        switch (ch) {
            case KEY_UP:    PlayerMove(move_up, &base_map, &player); break;
            case KEY_DOWN:  PlayerMove(move_down, &base_map, &player); break;
            case KEY_LEFT:  PlayerMove(move_left, &base_map, &player); break;
            case KEY_RIGHT: PlayerMove(move_right, &base_map, &player); break;
        }
    }

    endwin();
    return 0;
}

void DrawMap(maps *map) {
    for (int row = 0; row < MAP_ROW; row++) {
        for (int col = 0; col < MAP_COL; col++) {
            mvprintw(row, col * 2, "%c", map->map[row][col]);
        }
    }
}

void PlayerSpawn(maps *map, Player *player) {
    player->coords[0] = 1;
    player->coords[1] = 1;
    map->map[1][1] = player->sprite;
}

void PlayerMove(int move, maps *map, Player *player) {
    int x = player->coords[xAxis];
    int y = player->coords[yAxis];
    
    int new_x = x, new_y = y;
    switch (move) {
        case move_up:    new_x--; break;
        case move_down:  new_x++; break;
        case move_left:  new_y--; break;
        case move_right: new_y++; break;
    }
    
    if (map->map[new_x][new_y] == ' ') {
        map->map[x][y] = ' ';
        map->map[new_x][new_y] = player->sprite;
        player->coords[xAxis] = new_x;
        player->coords[yAxis] = new_y;
    }
}
