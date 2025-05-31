#include "../include/cub3d.h"

/**
 * @brief Recursive flood fill algorithm to check map boundaries
 * 
 * This function implements a recursive flood fill algorithm starting from
 * the player's position. It marks visited cells with 'F' and checks if
 * the player can "leak" outside the map (which would indicate the map
 * is not properly enclosed by walls).
 * 
 * @param vars The main program structure
 * @param row Current row in the map
 * @param col Current column in the map
 * @param size Total number of rows in the map
 * @return OK if the area is properly enclosed, ERROR if a boundary leak is found
 */
static int	f_fill(t_vars *vars, int row, int col, int size)
{
	int	row_length;

	if (row < 0 || row >= size)
		return (ERROR);
	row_length = ft_strlen(vars->map[row]);
	if (col < 0 || col >= row_length)
		return (ERROR);
	if (vars->map[row][col] == '1' || vars->map[row][col] == ' '
		|| vars->map[row][col] == 'F')
		return (OK);
	vars->map[row][col] = 'F';
	if (f_fill(vars, row - 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row + 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col - 1, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col + 1, size) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Start the flood fill algorithm from player's position
 * 
 * This function initiates the flood fill algorithm from the player's
 * starting position to check if the map is properly enclosed.
 * 
 * @param vars The main program structure
 * @param size Total number of rows in the map
 * @return OK if map is properly enclosed, ERROR otherwise
 */
static int	flood_fill(t_vars *vars, int size)
{
	return (f_fill(vars, vars->player->x_start, vars->player->y_start, size));
}

/**
 * @brief Check if the map is properly enclosed using flood fill
 * 
 * This function verifies that the player cannot reach the edge of the map,
 * which would indicate that the map is not fully enclosed by walls.
 * It uses a flood fill algorithm starting from the player's position.
 * 
 * @param vars The main program structure
 * @return OK if map is properly enclosed, ERROR otherwise
 */
int	check_flood(t_vars *vars)
{
	int	size;

	size = 0;
	if (vars->player->x_start < 0 || vars->player->y_start < 0)
		return (ERROR);
	while (vars->map[size])
		size++;
	return (flood_fill(vars, size));
}
