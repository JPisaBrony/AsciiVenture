#include "map.h"

void render_tile(int x, int y, tile *t) {
    int i, j;

    //printw(t->data);
    for(i = 0; i < TILE_SIZE; i++) {
        for(j = 0; j < TILE_SIZE; j++) {
            addch(t->data[i][j]);
        }
        printw("\n");
    }

    refresh();
}
