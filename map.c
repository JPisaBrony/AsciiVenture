#include "map.h"

/// print tile at x and y coordinate
// uses the upper left hand corner as the starting point for rendering the tile
// x is the x cord of the map
// y is the y cord of the map
// t is the tile to be rendered
// win is the screen to be rendered too
void render_tile(int x, int y, tile *t, WINDOW *win) {
    int i, j;
    // iterate through all of the characters in the tile
    for(i = 0; i < TILE_SIZE; i++) {
        for(j = 0; j < TILE_SIZE; j++) {
            // put character in tile at proper location
            mvwaddch(win, y + i, x + j, t->data[i][j]);
        }
    }
}

/// render a filled in room
// uses the upper left hand corner as the starting point for rendering the room
// wall is the tile to be used for the wall of the room
// height is the height of the room
// width is the width of the room
// win is the screen to be rendered too
void render_filled_room(tile *wall, int height, int width, WINDOW *win) {
    int i, j, x = 0, y = 0;

    // iterate through each position
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            // place the tile
            render_tile(x, y, wall, win);
            // update x position
            x += TILE_SIZE;
        }
        // update y position
        y += TILE_SIZE;
        // reset x
        x = 0;
    }
}

/// render a normal room
// uses the upper left hand corner as the starting point for rendering the room
// wall is the tile to be used for the wall of the room
// height is the height of the room
// width is the width of the room
// win is the screen to be rendered too
void render_room(tile *wall, int height, int width, WINDOW *win) {
    int i, x = 0, y = 0;

    // render top wall
    for(i = 0; i < width; i++) {
        render_tile(x, y, wall, win);
        x += TILE_SIZE;
    }
    // render bottom wall
    x = 0;
    y = (height - 1) * TILE_SIZE;
    for(i = 0; i < width; i++) {
        render_tile(x, y, wall, win);
        x += TILE_SIZE;
    }
    // render left wall
    x = 0;
    y = 0;
    for(i = 0; i < height; i++) {
        render_tile(x, y, wall, win);
        y += TILE_SIZE;
    }
    // render right wall
    x = (width - 1) * TILE_SIZE;
    y = 0;
    for(i = 0; i < height; i++) {
        render_tile(x, y, wall, win);
        y += TILE_SIZE;
    }
}
