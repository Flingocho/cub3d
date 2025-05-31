#include "../include/cub3d.h"

/**
 * @brief Initialize the game's graphical components
 *
 * This function sets up the MLX library, creates the game window,
 * and initializes the main image buffer used for rendering.
 * It handles both regular and bonus mode window creation.
 *
 * @param vars Pointer to the main program structure
 */
static void	init_game(t_vars *vars)
{
	vars->game->mlx = mlx_init();
	if (!vars->game->mlx)
		return (perror("mlx"), exit(ERROR));
	if (BONUS)
		vars->game->win = mlx_new_window(vars->game->mlx, WIDTH, HEIGHT,
				"Cub3d_bonus");
	else
		vars->game->win = mlx_new_window(vars->game->mlx, WIDTH, HEIGHT,
				"Cub3d");
	if (!vars->game->win)
		return (perror("mlx"), exit(ERROR));
	vars->game->img.img = mlx_new_image(vars->game->mlx, WIDTH, HEIGHT);
	if (!vars->game->img.img)
		return (perror("mlx"), exit(ERROR));
	vars->game->img.addr = mlx_get_data_addr(vars->game->img.img,
			&vars->game->img.bpp, &vars->game->img.line_length,
			&vars->game->img.endian);
	vars->game->world_map = NULL;
}

/**
 * @brief Initialize all program structures and resources
 *
 * This function allocates and initializes all main data structures
 * needed for the program, including game state, player info, and
 * configuration data. It also sets up initial values and
 * initializes the graphics components.
 *
 * @param vars Pointer to the pointer that will store the main structure
 */
void	init_vars(t_vars **vars)
{
	*vars = ft_calloc(1, sizeof(t_vars));
	if (!*vars)
		return (perror("malloc"), exit(ERROR));
	(*vars)->game = ft_calloc(1, sizeof(t_game));
	(*vars)->player = ft_calloc(1, sizeof(t_player));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
	if (!(*vars)->game || !(*vars)->player || !(*vars)->paths
		|| !(*vars)->colors)
		return (perror("malloc"), exit(ERROR));
	(*vars)->map_path_fd = 0;
	(*vars)->bytes_read = 0;
	(*vars)->map_path = NULL;
	(*vars)->buffer = NULL;
	(*vars)->file = NULL;
	(*vars)->map = NULL;
	init_game((*vars));
}
