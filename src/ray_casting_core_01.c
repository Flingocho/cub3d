/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_core_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:50:28 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 13:25:31 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	select_door_tex(t_game *game, int i, t_img *texture)
{
	if (i <= 10000)
		*texture = game->textures[DOOR1];
	else if (i <= 20000)
		*texture = game->textures[DOOR2];
	else if (i <= 30000)
		*texture = game->textures[DOOR3];
	else if (i <= 40000)
		*texture = game->textures[DOOR4];
}

static void	select_texture(t_game *game, t_ray_cast *rc, t_img *texture)
{
	static int	i;

	if (game->world_map[rc->mapY][rc->mapX] == 2)
	{
		if (i >= 40000)
			i = 0;
		select_door_tex(game, i, texture);
	}
	else if (rc->side == 1)
	{
		if (rc->rayDirY < 0)
			*texture = game->textures[NORTH];
		else
			*texture = game->textures[SOUTH];
	}
	else
	{
		if (rc->rayDirX < 0)
			*texture = game->textures[WEST];
		else
			*texture = game->textures[EAST];
	}
	i++;
}

static double	calculate_perp_wall_dist(t_game *game, t_ray_cast *rc)
{
	double	perpWallDist;
	double	adjustment;

	if (rc->side == 0)
	{
		adjustment = 1;
		if (rc->rayDirX < 0)
			adjustment = -1;
		perpWallDist = (rc->mapX - game->player_x + (1 - adjustment) / 2)
			/ rc->rayDirX;
	}
	else
	{
		adjustment = 1;
		if (rc->rayDirY < 0)
			adjustment = -1;
		perpWallDist = (rc->mapY - game->player_y + (1 - adjustment) / 2)
			/ rc->rayDirY;
	}
	return (perpWallDist);
}

static void	calculate_wall_params(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw)
{
	rcw->perpWallDist = calculate_perp_wall_dist(game, rc);
	rcw->lineHeight = (int)(HEIGHT / rcw->perpWallDist);
	rcw->drawStart = (HEIGHT - rcw->lineHeight) / 2;
	rcw->drawEnd = (HEIGHT + rcw->lineHeight) / 2;
	if (rcw->drawStart < 0)
		rcw->drawStart = 0;
	if (rcw->drawEnd >= HEIGHT)
		rcw->drawEnd = HEIGHT - 1;
	rcw->texNum = game->world_map[rc->mapY][rc->mapX] - 1;
}

void	render_column(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	t_ray_cast_draw	rcw;
	t_img			texture;

	calculate_wall_params(game, rc, &rcw);
	select_texture(game, rc, &texture);
	calculate_texture_coordinates(game, rc, &rcw, &texture);
	draw_wall_column(game, rc, &rcw, &texture);
	draw_ceiling_and_floor(game, rc, &rcw, vars);
}
