#include "map.h"

// print tile at x and y coordinate
// uses the upper left hand corner as the starting point for rendering the tile
// x is the x cord of the map
// y is the y cord of the map\
// tile is the tile to be rendered
// win is the screen to be rendered too
void render_tile(int x, int y, tile *t, WINDOW *win) {
    int i, j;
    // iterate through all of the characters in the tile
    for(i = 0; i < TILE_SIZE; i++) {
        for(j = 0; j < TILE_SIZE; j++) {
            // put character in tile at proper location
            mvwaddch(win, x + i, y + j, t->data[i][j]);
        }
    }
    // update the screen
    refresh();
}
