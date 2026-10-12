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

#include "dungeon_generator.h"

typedef enum{
    Floor,
    Wall,
    Nothing
}CellState

typedef struct{
    size_t x_value;
    size_t y_value;
    CelLState current_state;
}cell
