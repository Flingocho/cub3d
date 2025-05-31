#include "../include/cub3d.h"

/**
 * @brief Clean up all resources and exit the program
 *
 * This function performs comprehensive cleanup of all allocated resources,
 * including:
 * 1. MLX graphics resources (images, windows, display)
 * 2. Textures and game data
 * 3. Map data and configuration
 * 4. All dynamically allocated structures
 *
 * It's called before program termination to prevent memory leaks.
 *
 * @param vars The main program structure containing all resources
 */
void	clean_exit(t_vars *vars)
{
	mlx_loop_end(vars->game->mlx);
	mlx_destroy_image(vars->game->mlx, vars->game->img.img);
	free_textures(vars->game);
	mlx_destroy_window(vars->game->mlx, vars->game->win);
	mlx_destroy_display(vars->game->mlx);
	free(vars->game->mlx);
	free_char_matrix(vars->file);
	free_int_matrix(vars, vars->game->world_map);
	free_paths(vars);
	free_colors(vars);
	free(vars->paths);
	free(vars->player);
	free(vars->colors);
	free(vars->game);
	free(vars);
}
