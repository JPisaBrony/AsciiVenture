#include <stdio.h>
#include "curses.h"
#include <SDL/SDL.h>
#include "tile.h"
#include "player.h"
#include "map.h"
#include "globals.h"

PDCEX SDL_Surface *pdc_screen;
int quit = 0, direction;
char input_char;

int main(int argc, char* args[])
{
    // make SDL not write stdout.txt and stderr.txt to the filesystem
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    // initialize SDL and quit if it failed
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        exit(1);

    // setup SDL window
    pdc_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_SWSURFACE | SDL_ANYFORMAT);

    // init PDCurses with proper settings
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    nodelay(stdscr, TRUE);
    noecho();

    // blank tile
    char blank_data[4][4] = {
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ',' ' },
        { ' ', ' ', ' ', ' ' }
    };

    // create blank tile
    tile *blank_tile = create_tile(COLOR_WHITE, COLOR_BLUE, blank_data, "blank");

    // test tile
    char tile_data[4][4] = {
        { '-', '-', '-', '-' },
        { '|', ' ', ' ', '|' },
        { '|', ' ', ' ','|' },
        { '-', '-', '-', '-' }
    };

    // create testing tile
    tile *test_tile = create_tile(COLOR_WHITE, COLOR_BLUE, tile_data, "test tile");

    // create player tile
    char player_data[4][4] = {
        { '-', ' ', ' ', '-' },
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ',' ' },
        { '-', '-', '-', '-' }
    };

    // create player tile
    tile *player_tile = create_tile(COLOR_WHITE, COLOR_BLUE, player_data, "player");
    // create player
    player *player = create_player(4, 4, player_tile);

    // create screen
    screen *current_screen = create_screen();
    // set all the tiles to be blank
    initialize_level(blank_tile);
    // create a normal room
    add_room(test_tile, 5, 10);

    // main game loop
    while(!quit) {
        // get input character
        input_char = getch();
        switch(input_char) {
            // quit
            case 'q':
                quit = 1;
                break;
            // up
            case 'w':
                current_screen->y -= 1;
                player->direction = 1;
                move_player(player->x, player->y - TILE_SIZE, player);
                break;
            // left
            case 'a':
                current_screen->x -= 1;
                player->direction = 2;
                move_player(player->x - TILE_SIZE, player->y, player);
                break;
            // down
            case 's':
                current_screen->y += 1;
                player->direction = 3;
                move_player(player->x, player->y + TILE_SIZE, player);
                break;
            // right
            case 'd':
                current_screen->x += 1;
                player->direction = 4;
                move_player(player->x + TILE_SIZE, player->y, player);
                break;
        }

        /*
        // render the player
        render_player(player, blank_tile, stdscr);
        // reset direction
        player->direction = 0;

        // render the map
        render_room(test_tile, 10, 30, stdscr);
        refresh();
        */
        render_level(current_screen, stdscr);
    }

    // cleanup
    endwin();
    SDL_Quit();
    return 0;
}
