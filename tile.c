#include <stdlib.h>
#include "tile.h"

tile* create_tile(int bgcolor, int fgcolor, char data[TILE_SIZE][TILE_SIZE]) {
    tile *cur_tile = malloc(sizeof(tile));
    cur_tile->bgcolor = bgcolor;
    cur_tile->fgcolor = fgcolor;
    memcpy(cur_tile->data, data, TILE_SIZE * TILE_SIZE);
    return cur_tile;
}
