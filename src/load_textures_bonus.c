#include "../include/cub3d.h"

/**
 * @brief Loads the first door texture (bonus feature)
 *
 * Loads the first door animation frame from a hardcoded file path "textures/door_1.xpm"
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param game Game structure containing the MLX context and texture arrays
 */
static void	door1(t_game *game)
{
	char	path[20];

	ft_strlcpy(path, "textures/door_1.xpm", sizeof(path));
	game->textures[4].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[4].width, &game->textures[4].height);
	if (!game->textures[4].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[4].addr = mlx_get_data_addr(game->textures[4].img,
			&game->textures[4].bpp, &game->textures[4].line_length,
			&game->textures[4].endian);
}

/**
 * @brief Loads the second door texture (bonus feature)
 *
 * Loads the second door animation frame from a hardcoded file path "textures/door_2.xpm"
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param game Game structure containing the MLX context and texture arrays
 */
static void	door2(t_game *game)
{
	char	path[20];

	ft_strlcpy(path, "textures/door_2.xpm", sizeof(path));
	game->textures[5].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[5].width, &game->textures[5].height);
	if (!game->textures[5].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[5].addr = mlx_get_data_addr(game->textures[5].img,
			&game->textures[5].bpp, &game->textures[5].line_length,
			&game->textures[5].endian);
}

/**
 * @brief Loads the third door texture (bonus feature)
 *
 * Loads the third door animation frame from a hardcoded file path "textures/door_3.xpm"
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param game Game structure containing the MLX context and texture arrays
 */
static void	door3(t_game *game)
{
	char	path[20];

	ft_strlcpy(path, "textures/door_3.xpm", sizeof(path));
	game->textures[6].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[6].width, &game->textures[6].height);
	if (!game->textures[6].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[6].addr = mlx_get_data_addr(game->textures[6].img,
			&game->textures[6].bpp, &game->textures[6].line_length,
			&game->textures[6].endian);
}

/**
 * @brief Loads the fourth door texture (bonus feature)
 *
 * Loads the fourth door animation frame from a hardcoded file path "textures/door_4.xpm"
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param game Game structure containing the MLX context and texture arrays
 */
static void	door4(t_game *game)
{
	char	path[20];

	ft_strlcpy(path, "textures/door_4.xpm", sizeof(path));
	game->textures[7].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[7].width, &game->textures[7].height);
	if (!game->textures[7].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[7].addr = mlx_get_data_addr(game->textures[7].img,
			&game->textures[7].bpp, &game->textures[7].line_length,
			&game->textures[7].endian);
}

/**
 * @brief Loads all bonus textures for animated doors
 *
 * Loads all four animated door textures by calling the 
 * individual loading functions in sequence. These textures
 * are only loaded when the program is compiled with the BONUS
 * flag enabled.
 *
 * @param vars Main program variables structure containing the game data
 * @return OK if all textures are successfully loaded
 */
int	load_textures_bonus(t_vars *vars)
{
	door1(vars->game);
	door2(vars->game);
	door3(vars->game);
	door4(vars->game);
	return (OK);
}
