/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_core_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:50:28 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/15 13:50:48 by mrubal-c         ###   ########.fr       */
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

	if (game->world_map[rc->map_y][rc->map_x] == 2)
	{
		if (i >= 40000)
			i = 0;
		select_door_tex(game, i, texture);
	}
	else if (rc->side == 1)
	{
		if (rc->ray_dir_y < 0)
			*texture = game->textures[NORTH];
		else
			*texture = game->textures[SOUTH];
	}
	else
	{
		if (rc->ray_dir_x < 0)
			*texture = game->textures[WEST];
		else
			*texture = game->textures[EAST];
	}
	i++;
}

static double	calculate_perp_wall_dist(t_game *game, t_ray_cast *rc)
{
	double	perp_wall_dist;
	double	adjustment;

	if (rc->side == 0)
	{
		adjustment = 1;
		if (rc->ray_dir_x < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_x - game->player_x + (1 - adjustment) / 2)
			/ rc->ray_dir_x;
	}
	else
	{
		adjustment = 1;
		if (rc->ray_dir_y < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_y - game->player_y + (1 - adjustment) / 2)
			/ rc->ray_dir_y;
	}
	return (perp_wall_dist);
}

static void	calculate_wall_params(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw)
{
	rcw->perp_wall_dist = calculate_perp_wall_dist(game, rc);
	rcw->line_height = (int)(HEIGHT / rcw->perp_wall_dist);
	rcw->draw_start = (HEIGHT - rcw->line_height) / 2;
	rcw->draw_end = (HEIGHT + rcw->line_height) / 2;
	if (rcw->draw_start < 0)
		rcw->draw_start = 0;
	if (rcw->draw_end >= HEIGHT)
		rcw->draw_end = HEIGHT - 1;
	rcw->tex_num = game->world_map[rc->map_y][rc->map_x] - 1;
}

void	render_column(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	t_ray_cast_draw	rcw;
	t_img			texture;

	calculate_wall_params(game, rc, &rcw);
	select_texture(game, rc, &texture);
	calculate_texture_coordinates(game, rc, &rcw, &texture);
	draw_wall_column(game, rc, &rcw, &texture);
	draw_ceiling_and_floor(rc, &rcw, vars);
}
