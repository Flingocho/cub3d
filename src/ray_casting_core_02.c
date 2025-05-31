#include "../include/cub3d.h"

/**
 * @brief Renders the ceiling and floor for a single screen column
 *
 * Draws the ceiling portion (above the wall) and floor portion (below the wall)
 * for the current screen column. Applies fog effect by adjusting the color
 * intensity based on the distance from the viewer, creating depth perception.
 *
 * @param rc Raycasting information for the current column
 * @param rcw Wall rendering parameters including height and boundaries
 * @param vars Main program variables structure containing color settings
 */
void	draw_ceiling_and_floor(t_ray_cast *rc, t_ray_cast_draw *rcw,
		t_vars *vars)
{
	int		x;
	double	current_dist;

	x = rc->x;
	rcw->y = 0;
	while (rcw->y < rcw->draw_start)
	{
		current_dist = 1.0;
		if (HEIGHT - 2 * rcw->y != 0)
			current_dist = HEIGHT / (double)(HEIGHT - 2 * rcw->y);
		put_pixel_fog_ceiling(vars, x, rcw->y, current_dist);
		rcw->y++;
	}
	rcw->y = rcw->draw_end;
	while (rcw->y < HEIGHT)
	{
		current_dist = 1.0;
		if (2 * rcw->y - HEIGHT != 0)
			current_dist = HEIGHT / (double)(2 * rcw->y - HEIGHT);
		put_pixel_fog_floor(vars, x, rcw->y, current_dist);
		rcw->y++;
	}
}

/**
 * @brief Renders a textured wall column on the screen
 *
 * Maps the appropriate texture to the wall slice in the current screen column.
 * For each vertical pixel in the wall, calculates the corresponding texture 
 * coordinate, retrieves the color from the texture, applies fog effect based
 * on distance, and draws the pixel to the screen buffer.
 *
 * @param game Game structure containing the image buffer
 * @param rc Raycasting information for the current column
 * @param rcw Wall rendering parameters including height and texture coordinates
 * @param texture The texture to map onto the wall slice
 */
void	draw_wall_column(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw,
		t_img *texture)
{
	rcw->y = rcw->draw_start;
	while (rcw->y < rcw->draw_end)
	{
		rcw->d = rcw->y * 256 - HEIGHT * 128 + rcw->line_height * 128;
		rcw->tex_y = ((rcw->d * texture->height) / rcw->line_height) / 256;
		if (rcw->tex_y < 0)
			rcw->tex_y = 0;
		else if (rcw->tex_y >= texture->height)
			rcw->tex_y = texture->height - 1;
		rcw->color = *(unsigned int *)(texture->addr + (rcw->tex_y
					* texture->line_length + rcw->tex_x * (texture->bpp / 8)));
		put_pixel_fog_walls(&game->img, rc->x, rcw);
		rcw->y++;
	}
}

/**
 * @brief Calculates texture coordinates for mapping textures onto walls
 *
 * Determines the exact position on the wall where the ray hit, and converts
 * this to a corresponding x-coordinate in the texture. Adjusts the texture
 * coordinate based on the wall orientation and ray direction to ensure
 * correct texture mapping (flipping textures when needed).
 *
 * @param game Game structure containing player position
 * @param rc Raycasting information including ray direction and side hit
 * @param rcw Structure to store calculated texture coordinates
 * @param texture The texture to be mapped, used for dimension information
 */
void	calculate_texture_coordinates(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw, t_img *texture)
{
	if (rc->side == 0)
		rcw->wall_x = game->player_y + rcw->perp_wall_dist * rc->ray_dir_y;
	else
		rcw->wall_x = game->player_x + rcw->perp_wall_dist * rc->ray_dir_x;
	rcw->wall_x -= floor(rcw->wall_x);
	rcw->tex_x = (int)(rcw->wall_x * (double)(texture->width));
	if ((rc->side == 0 && rc->ray_dir_x > 0) || (rc->side == 1
			&& rc->ray_dir_y < 0))
		rcw->tex_x = texture->width - rcw->tex_x - 1;
}
