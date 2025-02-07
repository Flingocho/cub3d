/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_core_02                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:27 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 13:29:33 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	apply_fog(int color, double distance, double max_distance)
{
	double	fogFactor;
	int fogColor = 0x000000;
	int rgb[3];
	int fog[3];
	int new[3];

	fogFactor = distance / max_distance;
	if (fogFactor > 1.0)
		fogFactor = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	fog[0] = (fogColor >> 16) & 0xFF;
	fog[1] = (fogColor >> 8) & 0xFF;
	fog[2] = fogColor & 0xFF;
	new[0] = (int)(rgb[0] * (1.0 - fogFactor) + fog[0] * fogFactor);
	new[1] = (int)(rgb[1] * (1.0 - fogFactor) + fog[1] * fogFactor);
	new[2] = (int)(rgb[2] * (1.0 - fogFactor) + fog[2] * fogFactor);
	return ((new[0] << 16) | (new[1] << 8) | new[2]);
}

static void	put_pixel_fog(t_img *img, int x, int y, int color, double fogDistance,
		double max_distance)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(color, fogDistance, max_distance);
	}
}

void	draw_ceiling_and_floor(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw, t_vars *vars)
{
	int		x;
	double	currentDist;

	x = rc->x;
	rcw->y = 0;
	while (rcw->y < rcw->drawStart)
	{
		currentDist = 1.0;
		if (HEIGHT - 2 * rcw->y != 0)
			currentDist = HEIGHT / (double)(HEIGHT - 2 * rcw->y);
		put_pixel_fog(&game->img, x, rcw->y, vars->colors->c_hex, currentDist,
				10.0);
		rcw->y++;
	}
	rcw->y = rcw->drawEnd;
	while (rcw->y < HEIGHT)
	{
		currentDist = 1.0;
		if (2 * rcw->y - HEIGHT != 0)
			currentDist = HEIGHT / (double)(2 * rcw->y - HEIGHT);
		put_pixel_fog(&game->img, x, rcw->y, vars->colors->f_hex, currentDist,
				10.0);
		rcw->y++;
	}
}

void	draw_wall_column(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw,
		t_img *texture)
{
	rcw->y = rcw->drawStart;
	while (rcw->y < rcw->drawEnd)
	{
		rcw->d = rcw->y * 256 - HEIGHT * 128 + rcw->lineHeight * 128;
		rcw->texY = ((rcw->d * texture->height) / rcw->lineHeight) / 256;
		rcw->color = *(unsigned int *)(texture->addr + (rcw->texY
					* texture->line_length + rcw->texX * (texture->bpp / 8)));
		put_pixel_fog(&game->img, rc->x, rcw->y, rcw->color, rcw->perpWallDist,
				10.0);
		rcw->y++;
	}
}

void	calculate_texture_coordinates(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw, t_img *texture)
{
	if (rc->side == 0)
		rcw->wallX = game->player_y + rcw->perpWallDist * rc->rayDirY;
	else
		rcw->wallX = game->player_x + rcw->perpWallDist * rc->rayDirX;
	rcw->wallX -= floor(rcw->wallX);
	rcw->texX = (int)(rcw->wallX * (double)(texture->width));
	if ((rc->side == 0 && rc->rayDirX > 0) || (rc->side == 1
			&& rc->rayDirY < 0))
		rcw->texX = texture->width - rcw->texX - 1;
}
