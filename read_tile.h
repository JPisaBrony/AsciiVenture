#include "tile.h"

#ifndef READ_TILE_H_INCLUDED
#define READ_TILE_H_INCLUDED

typedef struct {
    struct tile_node_t** head;
    struct tile_node_t** last;
} tile_list_t;

typedef struct {
    struct tile* data;
    struct tile_node_t* next;
    struct tile_node_t* prev;
} tile_node_t;

int Length(struct tile* head);

struct tile seek();

tile_list_t* init_tiles();

void init_list(tile_list_t** tlist, tile* t, int j);

#endif // READ_TILE_H_INCLUDED
