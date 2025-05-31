#include "../include/cub3d.h"

/**
 * @brief Applies a distance-based fog effect to a color
 *
 * Mixes the original color with a fog color (black by default) based on distance.
 * As distance increases, the color gradually fades to the fog color, creating
 * a depth perception effect. The function breaks down the colors into RGB components,
 * interpolates them based on fog factor, and recombines them.
 *
 * @param color Original RGB color value
 * @param distance Distance from the viewer
 * @param max_distance Maximum distance before fog is at full effect
 * @return Modified color with fog effect applied
 */
static int	apply_fog(int color, double distance, double max_distance)
{
	double	fog_factor;
	int		fog_color;
	int		rgb[3];
	int		fog[3];
	int		new[3];

	fog_color = 0x000000;
	fog_factor = distance / max_distance;
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	fog[0] = (fog_color >> 16) & 0xFF;
	fog[1] = (fog_color >> 8) & 0xFF;
	fog[2] = fog_color & 0xFF;
	new[0] = (int)(rgb[0] * (1.0 - fog_factor) + fog[0] * fog_factor);
	new[1] = (int)(rgb[1] * (1.0 - fog_factor) + fog[1] * fog_factor);
	new[2] = (int)(rgb[2] * (1.0 - fog_factor) + fog[2] * fog_factor);
	return ((new[0] << 16) | (new[1] << 8) | new[2]);
}

/**
 * @brief Draws a pixel on the floor with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the floor color based on the distance from the viewer.
 * Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param vars Main program variables structure containing floor color
 * @param x X-coordinate in the image buffer
 * @param y Y-coordinate in the image buffer
 * @param fogDistance Distance value used to calculate fog intensity
 */
void	put_pixel_fog_floor(t_vars *vars, int x, int y, double fogDistance)
{
	t_img	*img;
	double	max_distance;
	char	*dst;

	img = &vars->game->img;
	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(vars->colors->f_hex, fogDistance,
				max_distance);
	}
}

/**
 * @brief Draws a pixel on the ceiling with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the ceiling color based on the distance from the viewer.
 * Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param vars Main program variables structure containing ceiling color
 * @param x X-coordinate in the image buffer
 * @param y Y-coordinate in the image buffer
 * @param fogDistance Distance value used to calculate fog intensity
 */
void	put_pixel_fog_ceiling(t_vars *vars, int x, int y, double fogDistance)
{
	t_img	*img;
	double	max_distance;
	char	*dst;

	img = &vars->game->img;
	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(vars->colors->c_hex, fogDistance,
				max_distance);
	}
}

/**
 * @brief Draws a pixel on a wall with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the wall texture color based on the perpendicular
 * wall distance. Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param img Image buffer to draw to
 * @param x X-coordinate in the image buffer
 * @param rcw Wall rendering information including Y-coordinate, color, and perpendicular distance
 */
void	put_pixel_fog_walls(t_img *img, int x, t_ray_cast_draw *rcw)
{
	double	max_distance;
	char	*dst;

	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && rcw->y >= 0 && rcw->y < HEIGHT)
	{
		dst = img->addr + (rcw->y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(rcw->color, rcw->perp_wall_dist,
				max_distance);
	}
}
