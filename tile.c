#include <stdlib.h>
#include "tile.h"

// create a tile
// bgcolor is the background color of the tile
// fgcolor is the forground color of the tile
// data is the character array of tile
tile* create_tile(int bgcolor, int fgcolor, char data[TILE_SIZE][TILE_SIZE], char *name) {
    tile *cur_tile = malloc(sizeof(tile));
    cur_tile->bgcolor = bgcolor;
    cur_tile->fgcolor = fgcolor;
    memcpy(cur_tile->data, data, TILE_SIZE * TILE_SIZE);
    cur_tile->name = name;
    return cur_tile;
}
