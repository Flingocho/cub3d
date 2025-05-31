#include "../include/cub3d.h"

/**
 * @brief Safely draws a pixel to an image buffer
 *
 * Writes a color value to a specific pixel in the image buffer,
 * but only if the coordinates are within the valid screen boundaries.
 * Used for clearing the screen and other drawing operations.
 *
 * @param img Image structure containing the buffer address and metadata
 * @param x X-coordinate of the pixel
 * @param y Y-coordinate of the pixel
 * @param color RGB color value to set at the specified pixel
 */
static void	put_pixel_clear(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * @brief Clears the entire image buffer to black
 *
 * Iterates through every pixel in the image buffer and sets it to
 * black (0x000000). This prepares the buffer for the next frame
 * to be drawn from scratch.
 *
 * @param img Image structure to be cleared
 */
static void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_clear(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the 3D scene using raycasting technique
 *
 * Performs the raycasting process for each vertical column of the screen.
 * For each column, calculates ray direction, initializes ray position and 
 * step values, then processes the ray until it hits a wall to determine
 * what to draw in that column.
 *
 * @param vars Main program variables structure
 * @param game Game structure containing player and map data
 */
static void	render_scene(t_vars *vars, t_game *game)
{
	t_ray_cast	rc;

	rc.x = 0;
	while (rc.x < WIDTH)
	{
		calculate_ray_direction(game, &rc);
		initialize_ray_position(game, &rc);
		initialize_step_and_sidedist(game, &rc);
		rc.hit = 0;
		process_ray_casting(game, vars, &rc);
		rc.x++;
	}
}

/**
 * @brief Main rendering function called on each frame
 *
 * Clears the previous frame, updates player movement based on active keys,
 * renders the 3D scene, and displays the result. In bonus mode, also draws
 * the mini-map and manages door animation cooldown.
 *
 * @param vars Main program variables structure containing game data
 * @return Always returns 0, required by the MLX loop hook API
 */
int	render(t_vars *vars)
{
	clear_image(&vars->game->img);
	update_movement(vars->game);
	render_scene(vars, vars->game);
	mlx_put_image_to_window(vars->game->mlx, vars->game->win,
		vars->game->img.img, 0, 0);
	if (BONUS)
		draw_minimap(vars->game);
	if (vars->game->door_cooldown > 0)
		vars->game->door_cooldown--;
	return (0);
}
