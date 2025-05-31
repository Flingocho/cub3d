#include "../include/cub3d.h"

/**
 * @brief Convert character map to integer grid for raycasting
 * 
 * This function transforms the map from its character representation ('0', '1', 'D')
 * into an integer grid for the raycasting engine:
 * - '0' (empty space) becomes 0
 * - 'D' (door) becomes 2
 * - Other characters (wall, spaces) become 1
 * 
 * @param vars The main program structure
 */
static void	set_matrix_int(t_vars *vars)
{
	int	i;
	int	j;
	int	row_length;

	i = 0;
	while (i < vars->game->map_height)
	{
		row_length = ft_strlen(vars->map[i]);
		j = 0;
		while (j < vars->game->map_width)
		{
			if (j < row_length && vars->map[i][j] == '0')
				vars->game->world_map[i][j] = 0;
			else if (j < row_length && vars->map[i][j] == 'D')
				vars->game->world_map[i][j] = 2;
			else
				vars->game->world_map[i][j] = 1;
			j++;
		}
		i++;
	}
}

/**
 * @brief Calculate map dimensions and allocate memory for the integer grid
 * 
 * This function:
 * 1. Calculates the height and maximum width of the map
 * 2. Allocates memory for the 2D integer grid representation
 * 3. Converts the character map to an integer grid
 * 4. Performs flood fill validation to ensure the map is enclosed
 * 
 * @param vars The main program structure
 * @return OK if successful, ERROR if memory allocation fails or map is invalid
 */
static int	map_dimensions(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if ((size_t)vars->game->map_width < ft_strlen(vars->map[i]))
			vars->game->map_width = ft_strlen(vars->map[i]);  /* Find max width */
		i++;
	}
	vars->game->map_height = i;
	i = 0;
	vars->game->world_map = calloc(vars->game->map_height, sizeof(int *));
	if (!vars->game->world_map)
		return (perror("malloc"), exit(1), ERROR);
	while (i < vars->game->map_height)
	{
		vars->game->world_map[i] = calloc(vars->game->map_width, sizeof(int));
		if (!vars->game->world_map[i++])
			return (perror("malloc"), exit(1), ERROR);
	}
	set_matrix_int(vars);
	if (check_flood(vars) == ERROR)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1),
			ERROR);
	return (OK);
}

/**
 * @brief Check that exactly one player starting position is defined
 * 
 * This function verifies that the map contains exactly one player starting
 * position marker (N, S, E, or W). Having zero or multiple starting positions
 * would make the map invalid.
 * 
 * @param map The 2D character array representing the map
 * @return OK if exactly one starting position exists, ERROR otherwise
 */
static int	check_repeated_position(char **map)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				counter++;
			j++;
		}
		i++;
	}
	if (counter == 1)
		return (OK);
	ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO);
	return (ERROR);
}

/**
 * @brief Master function for validating the map
 * 
 * This function performs several checks to ensure the map is valid:
 * 1. Verifies there's exactly one player starting position
 * 2. Ensures all characters in the map are valid
 * 3. Converts spaces to walls ('1') for proper boundary handling
 * 4. Processes map dimensions and creates the integer grid
 * 
 * @param vars The main program structure
 * @return OK if the map is valid, ERROR otherwise
 */
int	check_map_valid(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	if (check_repeated_position(vars->map) == ERROR)
		exit(ERROR);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (check_valid_charset(vars, vars->map[i][j], i, j) == ERROR)
				return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO),
					ERROR);
			if (vars->map[i][j] == ' ')
				vars->map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (map_dimensions(vars) == ERROR)
		return (ERROR);
	return (OK);
}
