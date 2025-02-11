/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:36:11 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 14:36:51 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
