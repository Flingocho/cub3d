/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_core_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:27 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/15 13:49:59 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
