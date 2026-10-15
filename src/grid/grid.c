#include <stdlib.h>
#include "grid.h"

DungeonGrid* dungeon_grid_create(size_t width, size_t height, size_t layer_index){
    DungeonGrid *grid = malloc(sizeof(DungeonGrid));
    if (!grid){
        return NULL;
    }

    grid->width = width;
    grid->height = height;
    grid->layer_index = layer_index;
    grid->tiles = calloc(width * height, sizeof(int));

    if(!grid->tiles){
        free(grid);
        return NULL;
    }
    return grid;
}

void dungeon_grid_free(DungeonGrid *grid){
    if(!grid){
        return;
    }
    free(grid->tiles);
    free(grid);
}

int dungeon_grid_get(const DungeonGrid *grid, size_t x, size_t y){
    if( !grid || x >= grid->width || y >= grid->height){
        return -1;
    }

    return grid->tiles[y * grid->width + x];
}

void dungeon_grid_set(DungeonGrid *grid, size_t x, size_t y, int value){
    if(!grid || x >= grid->width || y >= grid->height){
        return;
    }
    grid->tiles[y * grid->width + x] = value;
}
