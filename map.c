#include "map.h"

/// initialize a screen structure
screen* create_screen() {
    screen *s = malloc(sizeof(screen));
    s->x = 0;
    s->y = 0;
    s->width = (WIDTH / TILE_SIZE);
    s->height = (HEIGHT / TILE_SIZE);
}

/// initialize all the tiles in a level
// t the tile each tile to be initialize to
void initialize_level(tile *t) {
    int i, j;

    for(i = 0; i < LEVEL_SIZE; i++) {
        for(j = 0; j < LEVEL_SIZE; j++) {
            // set the dereferenced tile to be tile in the level
            level[i][j] = *t;
        }
    }
}

/// print the level using the current screen position
// s is the screen to be used
// win is the screen to be rendered too
void render_level(screen *s, WINDOW *win) {
    int i, j;
    // render the section of the level based on where the screen is
    for(i = 0; i < s->height; i++) {
        for(j = 0; j < s->width; j++) {
            // add the tile of were the screen is currently located
            render_tile(i * TILE_SIZE, j * TILE_SIZE, &level[s->x + i][s->y + j], win);
        }
    }
}

/// render tile at x and y coordinate
// uses the upper left hand corner as the starting point for rendering the tile
// x is the x cord of the screen
// y is the y cord of the screen
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

/// add tile to the level
// x is the x cord of the level
// y is the x cord of the level
// t is the tile to be added
void add_tile_to_level(int x, int y, tile *t) {
    level[x][y] = *t;
}

/// check to see if collision has been detected
// 0 is there is no collision
// 1 is there was a collision
// x is the x cord of the collision to be checked against
// y is the y cord of the collision to be checked against
// direction is the direction of the collision
// col_tile is the tile to be checked against
int check_collision(int x, int y, int direction, tile *col_tile) {
    int collision = 0;

    // select direction for checking collision
    switch(direction) {
        // up
        case 1:
            // check if at the boundary
            if(y > 0) {
                // check tile above if it equals the tile to collide with
                if(compare_tile_data(&level[x][y-1], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // left
        case 2:
            // check if at the boundary
            if(x > 0) {
                // check tile left of if it equals the tile to collide with
                if(compare_tile_data(&level[x-1][y], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // down
        case 3:
            // check if at the boundary
            if(y < LEVEL_SIZE) {
                // check tile below it equals the tile to collide with
                if(compare_tile_data(&level[x][y+1], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // right
        case 4:
            // check if at the boundary
            if(x < LEVEL_SIZE) {
                // check tile right of it equals the tile to collide with
                if(compare_tile_data(&level[x+1][y], col_tile)) {
                    collision = 1;
                }
            }
            break;
    }
    // return if it collided or not
    return collision;
}

/// add a filled in room to the level
// uses the upper left hand corner as the starting point for rendering the room
// wall is the tile to be used for the wall of the room
// height is the height of the room
// width is the width of the room
void add_filled_room(tile *wall, int height, int width) {
    int i, j, x = 0, y = 0;

    // iterate through each position
    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            // add the tile
            add_tile_to_level(i, j, wall);
        }
    }
}

/// add a normal room
// uses the upper left hand corner as the starting point for rendering the room
// wall is the tile to be used for the wall of the room
// height is the height of the room
// width is the width of the room
void add_room(tile *wall, int height, int width) {
    int i, x = 0, y = 0;

    // add top wall
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }
    // add bottom wall
    // set variables to proper values
    x = 0;
    y = (height - 1);
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }
    // add left wall
    // set variables to proper values
    x = 0;
    y = 0;
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }
    // add right wall
    // set variables to proper values
    x = (width - 1);
    y = 0;
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }
}
