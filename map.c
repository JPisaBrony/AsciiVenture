#include "map.h"

/// initialize a screen structure
screen* create_screen() {
    screen *s = malloc(sizeof(screen));
    s->x = LEVEL_CENTER;
    s->y = LEVEL_CENTER;
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

/// check to see if collided with the edge has been detected
// 0 is there is no collision
// 1 is there was a collision
// x is the x cord of the collision to be checked against
// y is the y cord of the collision to be checked against
// direction is the direction of the collision
int check_collision_edge(int x, int y, int direction) {
    int collision = 0;

    // select direction for checking collision
    switch(direction) {
        // up
        case 1:
            // check if at the boundary
            if(y > 0) {
                collision = 1;
            }
            break;
        // left
        case 2:
            // check if at the boundary
            if(x > 0) {
                collision = 1;
            }
            break;
        // down
        case 3:
            // check if at the boundary
            if(y < LEVEL_SIZE) {
                collision = 1;
            }
            break;
        // right
        case 4:
            // check if at the boundary
            if(x < LEVEL_SIZE) {
                collision = 1;
            }
            break;
    }
    // return if it collided or not
    return collision;
}

/// add a filled in room to the level
// uses the upper left hand corner as the starting point for rendering the room
// x_level is the x cord in the level
// y_level is the y cord in the level
// height is the height of the room
// width is the width of the room
// wall is the tile to be used for the wall of the room
void add_filled_room(int x_level, int y_level, int height, int width, tile *wall) {
    int i, j;

    // iterate through each position
    for(i = x_level; i < x_level + width; i++) {
        for(j = y_level; j < y_level + height; j++) {
            // add the tile
            add_tile_to_level(i, j, wall);
        }
    }
}

/// add a normal room
// uses the upper left hand corner as the starting point for rendering the room
// x_level is the x cord in the level
// y_level is the y cord in the level
// height is the height of the room
// width is the width of the room
// wall is the tile to be used for the wall of the room
void add_room(int x_level, int y_level, int height, int width, tile *wall) {
    int i, x = x_level, y = y_level;

    // add top wall
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level + (height - 1);
    // add bottom wall
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level;
    // add left wall
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }

    // set variables to proper values
    x = x_level + (width - 1);
    y = y_level;
    // add right wall
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }
}

/// add a hallway
// uses the upper left hand corner as the starting point for rendering the room
// x_level is the x cord in the level
// y_level is the y cord in the level
// height is the height of the room
// width is the width of the room
// path_x_offset is the offset used when rendering on either side of the wall section
// path_y_offset is the offset used when rendering on either side of the wall section
// path_width is used for determining the width of the path note: currently being used for offsets
// path_selection is which hallway to use
// wall is the tile to be used for the wall of the room
// blank is suppose to be the blank tile to clear sections of the walls
void add_hallway(int x_level, int y_level, int height, int width, int path_x_offset, int path_y_offset, int path_width, int path_selection, tile *wall, tile* blank) {
    int i, side_start_x, side_start_y, side_end_x, side_end_y, tile_remove_x, tile_remove_y;

    // get the proper length of each wall
    switch(path_selection) {
        case 1:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = path_x_offset + path_width + 1;
            side_end_y = path_y_offset + path_width + 1;
            break;
        case 2:
            side_start_x = path_x_offset;
            side_start_y = 0;
            side_end_x = width;
            side_end_y = path_y_offset + path_width;
            break;
        case 3:
            side_start_x = 0;
            side_start_y = path_y_offset;
            side_end_x = path_x_offset + path_width;
            side_end_y = height;
            break;
        case 4:
            side_start_x = path_x_offset;
            side_start_y = path_y_offset;
            side_end_x = width;
            side_end_y = height;
            break;
        case 5:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = width;
            side_end_y = 0;
            break;
        case 6:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = 0;
            side_end_y = height;
            break;
        case 7:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = path_x_offset;
            side_end_y = height;
            break;
        case 8:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = width;
            side_end_y = path_y_offset;
            break;
        case 9:
            side_start_x = path_x_offset + path_width;
            side_start_y = 0;
            side_end_x = width;
            side_end_y = height;
            break;
        case 10:
            side_start_x = 0;
            side_start_y = path_y_offset + path_width;
            side_end_x = width;
            side_end_y = height;
            break;
        case 11:
            side_start_x = 0;
            side_start_y = 0;
            side_end_x = width;
            side_end_y = height;
    }

    // add top part of hall along x axis
    for(i = side_start_x; i < side_end_x; i++) {
        // add the tile
        add_tile_to_level(x_level + i, x_level + path_y_offset, wall);
    }

    // add top part of hall along x axis
    for(i = side_start_x; i < side_end_x; i++) {
        // add the tile
        add_tile_to_level(x_level + i, y_level + 2 + path_y_offset, wall);
    }

    // add left part of hall along y axis
    for(i = side_start_y; i < side_end_y; i++) {
        // add the tile
        add_tile_to_level(x_level + path_x_offset, y_level + i, wall);
    }

    // add right part of hall along y axis
    for(i = side_start_y; i < side_end_y; i++) {
        // add the tile
        add_tile_to_level(x_level + 2 + path_x_offset, y_level + i, wall);
    }

    // remove extra squares
    switch(path_selection) {
        case 1:
            add_tile_to_level(x_level + side_end_x - 2, x_level + path_y_offset, blank);
            add_tile_to_level(x_level + path_x_offset, y_level + side_end_y - 2, blank);
            break;
        case 2:
            add_tile_to_level(x_level + side_start_x + 2, y_level + 2 + path_y_offset - 1, blank);
            add_tile_to_level(x_level + 2 + path_x_offset - 1, y_level + side_end_y - 2, blank);
            break;
        case 3:
            add_tile_to_level(x_level + side_end_x - 2, x_level + path_y_offset + 1, blank);
            add_tile_to_level(x_level + 2 + path_x_offset - 1, y_level + side_start_y + 2, blank);
            break;
        case 4:
            add_tile_to_level(x_level + side_start_x + 1, y_level + 2 + path_y_offset, blank);
            add_tile_to_level(x_level + 2 + path_x_offset, y_level + side_start_y + 1, blank);
            break;
        case 7:
            add_tile_to_level(x_level + side_end_x, x_level + path_y_offset + 1, blank);
            break;
        case 8:
            add_tile_to_level(x_level + 2 + path_x_offset - 1, y_level + side_end_y, blank);
            break;
        case 9:
            add_tile_to_level(x_level + side_start_x, y_level + 2 + path_y_offset - 1, blank);
            break;
        case 10:
            add_tile_to_level(x_level + 2 + path_x_offset - 1, y_level + side_start_y, blank);
            break;
        case 11:
            // add top part of hall along x axis
            for(i = side_start_x; i < side_end_x; i++) {
                // add the tile
                add_tile_to_level(x_level + i, y_level + 1 + path_y_offset, blank);
            }
            // add right part of hall along y axis
            for(i = side_start_y; i < side_end_y; i++) {
                // add the tile
                add_tile_to_level(x_level + 1 + path_x_offset, y_level + i, blank);
            }
            break;
    }
}
