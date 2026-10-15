#ifndef GRID_H
#define GRID_H

#include <stddef.h>
#include <stdbool.h>

typedef struct{
    int *tiles;
    size_t width;
    size_t height;
    size_t layer_index;
}DungeonGrid;

// Lifecycle
DungeonGrid* dungeon_grid_create(size_t width, size_t height, size_t layer_index);
void dungeon_grid_free(DungeonGrid *grid);

// Access
int dungeon_grid_get(const DungeonGrid *grid, size_t x, size_t y);
void dungeon_grid_set(DungeonGrid *grid, size_t x, size_t y, int value);

// I/O Functions
void dungeon_grid_print(const DungeonGrid *grid);
bool dungeon_grid_save_to_file(const DungeonGrid *grid, const char *filename);
DungeonGrid* dungeon_grid_load_from_file(const char *filename);

#endif
