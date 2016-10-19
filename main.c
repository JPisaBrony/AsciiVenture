#include <stdio.h>
#include <SDL/SDL.h>
#include "curses.h"
#include "tile.h"

#define WIDTH 1280
#define HEIGHT 720

PDCEX SDL_Surface *pdc_screen;

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
    scrollok(stdscr, TRUE);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    //nodelay(stdscr, TRUE);

    // test tile
    char tile_data[4][4] = {
        { '-', '-', '-', '-' },
        { '|', ' ', ' ', '|' },
        { '|', ' ', ' ','|' },
        { '-', '-', '-', '-' }
    };

    tile *test_tile = create_tile(COLOR_WHITE, COLOR_BLUE, tile_data);

    render_room(test_tile, 10, 30, stdscr);
    //render_filled_room(test_tile, 10, 30, stdscr);

    // wait
    getch();

    // cleanup
    endwin();
    SDL_Quit();
    return 0;
}
