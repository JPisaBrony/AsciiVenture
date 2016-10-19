#ifndef TILE_INCLUDED
#define TILE_INCLUDED

/// globals

#define TILE_SIZE 4

/// structures

// tile structure used to hold the data about each tile to be rendered
typedef struct {
    // background color of the tile
    int bgcolor;
    // foreground color of the tile
    int fgcolor;
    // characters contained in the tile
    char data[TILE_SIZE][TILE_SIZE];
    // name of the tile
    char *name;
} tile;


/// function prototypes

tile* create_tile(int bgcolor, int fgcolor, char data[TILE_SIZE][TILE_SIZE], char *name);

#endif // TILE_INCLUDED
