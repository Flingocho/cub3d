#include "../include/cub3d.h"

/**
 * @brief Handles mouse movement for player rotation (bonus feature)
 *
 * Tracks mouse movement along the x-axis to rotate the player's view.
 * Automatically recenters the mouse cursor to allow continuous rotation.
 * The rotation speed is adjusted by the sensitivity multiplier (0.001).
 *
 * @param x Current x-coordinate of the mouse cursor
 * @param y Current y-coordinate of the mouse cursor (unused)
 * @param game Game structure containing player data and window information
 * @return Always returns 0
 */
int	mouse_move(int x, int y, t_game *game)
{
	static int	center_x;
	double		angle;

	(void)y;
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		angle = (x - center_x) * 0.001;
		rotate_player(game, angle);
		mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	}
	return (0);
}

/**
 * @brief Displays an animated intro sequence with alternating title images
 *
 * Loads two title images and alternates them to create a simple animation
 * effect at the start of the game. The animation runs for 25 frames with
 * a 100ms delay between each frame. Handles memory cleanup after completion.
 *
 * @param mlx MLX graphics context pointer
 * @param win Game window pointer
 */
void	draw_images(void *mlx, void *win)
{
	void	*img1;
	void	*img2;
	int		i;

	img1 = mlx_xpm_file_to_image(mlx, "textures/title01.xpm", &(int){WIDTH},
			&(int){HEIGHT});
	if (!img1)
		return ;
	img2 = mlx_xpm_file_to_image(mlx, "textures/title02.xpm", &(int){WIDTH},
			&(int){HEIGHT});
	if (!img2)
		return ((void)mlx_destroy_image(mlx, img1));
	i = 0;
	while (i < 25)
	{
		if (i % 2 == 0)
			mlx_put_image_to_window(mlx, win, img1, 0, 0);
		else
			mlx_put_image_to_window(mlx, win, img2, 0, 0);
		usleep(100000);
		i++;
	}
	mlx_destroy_image(mlx, img1);
	mlx_destroy_image(mlx, img2);
}

/**
 * @brief Program entry point
 *
 * Initializes the game, validates command-line arguments, loads the map,
 * sets up textures, and establishes event hooks. The program runs in a
 * continuous loop until the user closes the window. In bonus mode, mouse
 * control for player rotation is enabled.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return 0 on successful program execution
 */
int	main(int argc, char *argv[])
{
	t_vars	*vars;

	init_vars(&vars);
	if (!(check_args(argc, argv, vars) == OK && check_map_valid(vars) == OK))
		exit(1);
	load_textures(vars);
	draw_images(vars->game->mlx, vars->game->win);
	mlx_mouse_hide(vars->game->mlx, vars->game->win);
	mlx_hook(vars->game->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->game->win, 3, 1L << 1, key_release, vars->game);
	mlx_hook(vars->game->win, 17, 0, close_window, vars);
	mlx_loop_hook(vars->game->mlx, render, vars);
	if (BONUS)
	{
		mlx_mouse_move(vars->game->mlx, vars->game->win, WIDTH / 2, HEIGHT / 2);
		mlx_hook(vars->game->win, 6, 1L << 6, mouse_move, vars->game);
	}
	mlx_loop(vars->game->mlx);
	clean_exit(vars);
	return (0);
}
