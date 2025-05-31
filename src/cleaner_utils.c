#include "../include/cub3d.h"

/**
 * @brief Free a dynamically allocated 2D character array
 *
 * This function properly deallocates a NULL-terminated 2D character array
 * by freeing each string and then freeing the array of pointers itself.
 *
 * @param mtx The 2D character array (matrix) to free
 */
void	free_char_matrix(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

/**
 * @brief Free a dynamically allocated 2D integer array
 *
 * This function properly deallocates a 2D integer array of known height
 * by freeing each row and then freeing the array of pointers itself.
 *
 * @param vars The main program structure (needed for map height)
 * @param mtx The 2D integer array (matrix) to free
 */
void	free_int_matrix(t_vars *vars, int **mtx)
{
	int	i;

	i = 0;
	while (i < vars->game->map_height)
		free(mtx[i++]);
	free(mtx);
}

/**
 * @brief Free all texture path strings
 *
 * This function deallocates all dynamically allocated strings that
 * store the paths to texture files (north, south, east, west).
 *
 * @param vars The main program structure
 */
void	free_paths(t_vars *vars)
{
	free(vars->paths->no);
	free(vars->paths->so);
	free(vars->paths->we);
	free(vars->paths->ea);
}

/**
 * @brief Free color string values
 *
 * This function deallocates the dynamically allocated strings that
 * store the ceiling and floor color values.
 *
 * @param vars The main program structure
 */
void	free_colors(t_vars *vars)
{
	free(vars->colors->c);
	free(vars->colors->f);
}

/**
 * @brief Free and destroy all loaded textures
 *
 * This function properly cleans up the texture resources by destroying
 * the MLX image objects. It handles both standard textures (first 4)
 * and optional bonus textures (next 4).
 *
 * @param game Pointer to the game structure containing textures
 */
void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	while (BONUS && i < 8)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}
