#ifndef MAP_INCLUDED
#define MAP_INCLUDED
#include "tile.h"
#include "curses.h"

/// function prototypes

void render_tile(int x, int y, tile *t, WINDOW* win);

#endif // MAP_INCLUDED
