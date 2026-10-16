#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

/*
 * Cellular Automata algorithm:
 * Requirements:
 *  * Dimension (size_t/int x & size_t/int y)
 *  * Repeating Amt (int/size_t)
 *  * Multi-Layered (bool enabled & random depth || bool enabled && fixed depth -- int)
 * Pseudocode:
 *  * create_empty_matrix()
 *  * initialize()
 *  * step = 0
 *  * while step < AmtRepeating
 *  *   check_neighbour_states(current_cell)
 *  *   if first_condition_met()
 *  *       change_state(current_cell)
 *  * end
 *  * if not check_correctness()
 *  *   connect_rooms()
 *
 */

#include "generator.h"
#include "grid/grid.h"

DungeonGrid* generate_cave_grid(const DungeonParams *params);

void free_cave_grid(DungeonGrid *grid);

#endif
