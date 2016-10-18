#ifndef TILE_INCLUDED
#define TILE_INCLUDED

// tile structure used to hold the data about each tile to be rendered
typedef struct {
    // background color of the tile
    int bgcolor;
    // foreground color of the tile
    int fgcolor;
    // characters contained in the tile
    char **data;
} tile;

#endif // TILE_INCLUDED
