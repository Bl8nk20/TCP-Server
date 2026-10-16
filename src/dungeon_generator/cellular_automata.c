#include <stdlib.h>
#include <stdbool.h>
#include "cellular_automata.h"

static bool is_boundary_cell(size_t x, size_t y, size_t width, size_t height){
    return (x == 0 || y == 0 || x == width - 1 || y == height - 1);
}

void free_cave_grid(DungeonGrid *grid){
    dungeon_grid_free(grid);
}

static void init_state(DungeonGrid *grid, unsigned int seed){
    srand(seed);
    for (size_t y = 0; y < grid->height; y++){
        for(size_t x = 0; x < grid-> width; x++){
            // Boundaries are always Walls
            if(is_boundary_cell(x, y, grid->width, grid->height)){
                dungeon_grid_set(grid, x, y, 1);
                continue;
            }
            int wall = (rand() % 100 < 45) ? 1 : 0;
            dungeon_grid_set(grid, x, y, wall);     
        }
    }
}

static int count_alive_neighbours(const DungeonGrid *grid, size_t x, size_t y){
    int wall_counter = 0;
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0){
                continue;
            }
            long nx = (long)x + dx;
            long ny = (long)y + dy;

            if(nx < 0 || nx >= (long)grid->width || ny < 0 || ny >= (long)grid->height){
                wall_counter++;
            }
            else{
                if(dungeon_grid_get(grid, (size_t)nx, (size_t)ny) == 1){
                    wall_counter++;
                }
            }
        }
    }

    return wall_counter;
}

static void apply_cellular_step(const DungeonGrid *source, DungeonGrid *target) {
    // Innere Zellen berechnen
    for (size_t y = 1; y < source->height - 1; y++) {
        for (size_t x = 1; x < source->width - 1; x++) {
            int neighbors = count_alive_neighbours(source, x, y);
            int current = dungeon_grid_get(source, x, y);
            int next_val = current;

            // CA-Regeln (Birth / Death limits)
            if (current == 1) {
                next_val = (neighbors < 4) ? 0 : 1;
            } else {
                next_val = (neighbors > 4) ? 1 : 0;
            }
            dungeon_grid_set(target, x, y, next_val);
        }
    }

    // Ränder konstant als Wände beibehalten
    for (size_t y = 0; y < source->height; y++) {
        dungeon_grid_set(target, 0, y, 1);
        dungeon_grid_set(target, source->width - 1, y, 1);
    }
    for (size_t x = 0; x < source->width; x++) {
        dungeon_grid_set(target, x, 0, 1);
        dungeon_grid_set(target, x, source->height - 1, 1);
    }
}

// Hauptfunktion für den Höhlengenerator
DungeonGrid* generate_cave_grid(const DungeonParams *params) {
    DungeonGrid *grid = dungeon_grid_create(params->width, params->height, 0);
    if (!grid) return NULL;

    // Temporäres Grid für die Iterationen (nutzt dieselbe Grid-Library!)
    DungeonGrid *temp_grid = dungeon_grid_create(params->width, params->height, 0);
    if (!temp_grid) {
        dungeon_grid_free(grid);
        return NULL;
    }

    init_state(grid, params->seed);

    int iterations = (params->amt_Repetitions > 0) ? params->amt_Repetitions : 5;
    for (int i = 0; i < iterations; i++) {
        apply_cellular_step(grid, temp_grid);
        
        // Ergebnis von temp_grid zurück in das Hauptgrid kopieren
        for (size_t y = 0; y < grid->height; y++) {
            for (size_t x = 0; x < grid->width; x++) {
                int val = dungeon_grid_get(temp_grid, x, y);
                dungeon_grid_set(grid, x, y, val);
            }
        }
    }

    dungeon_grid_free(temp_grid);
    return grid;
}
