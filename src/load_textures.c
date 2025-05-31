#include "../include/cub3d.h"

/**
 * @brief Loads the north texture from file path
 *
 * Loads the north texture from the XPM file specified in vars->paths->no
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param vars Main program variables structure containing paths and game data
 */
static void	north(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, vars->paths->no,
			&game->textures[0].width, &game->textures[0].height);
	if (!game->textures[0].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_length,
			&game->textures[0].endian);
	if (game->textures[0].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the south texture from file path
 *
 * Loads the south texture from the XPM file specified in vars->paths->so
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param vars Main program variables structure containing paths and game data
 */
static void	south(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, vars->paths->so,
			&game->textures[1].width, &game->textures[1].height);
	if (!game->textures[1].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_length,
			&game->textures[1].endian);
	if (game->textures[1].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the east texture from file path
 *
 * Loads the east texture from the XPM file specified in vars->paths->ea
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param vars Main program variables structure containing paths and game data
 */
static void	east(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, vars->paths->ea,
			&game->textures[2].width, &game->textures[2].height);
	if (!game->textures[2].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_length,
			&game->textures[2].endian);
	if (game->textures[2].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the west texture from file path
 *
 * Loads the west texture from the XPM file specified in vars->paths->we
 * and prepares the texture data for rendering. If the texture can't be loaded
 * or if the data address retrieval fails, the program exits with an error.
 *
 * @param vars Main program variables structure containing paths and game data
 */
static void	west(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, vars->paths->we,
			&game->textures[3].width, &game->textures[3].height);
	if (!game->textures[3].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_length,
			&game->textures[3].endian);
	if (game->textures[3].addr == NULL)
		exit(1);
}

/**
 * @brief Main texture loading function
 *
 * Orchestrates the loading of all directional textures (north, south, east, west).
 * If the program is compiled with the bonus feature enabled, additional textures
 * are loaded through the load_textures_bonus function.
 *
 * @param vars Main program variables structure containing texture paths and game data
 * @return OK if all textures are successfully loaded
 */
int	load_textures(t_vars *vars)
{
	north(vars);
	south(vars);
	east(vars);
	west(vars);
	if (BONUS)
		load_textures_bonus(vars);
	return (OK);
}
