/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:46:24 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/11 14:46:12 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	perform_dda(t_game *game, t_ray_cast *rc)
{
	while (!(rc->hit))
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->world_map[rc->map_y][rc->map_x] != 0
			&& game->world_map[rc->map_y][rc->map_x] != 3)
			rc->hit = 1;
	}
}

void	process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	perform_dda(game, rc);
	render_column(game, vars, rc);
}

void	initialize_step_and_sidedist(t_game *game, t_ray_cast *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player_y) * rc->delta_dist_y;
	}
}

void	initialize_ray_position(t_game *game, t_ray_cast *rc)
{
	rc->map_x = (int)game->player_x;
	rc->map_y = (int)game->player_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

void	calculate_ray_direction(t_game *game, t_ray_cast *rc)
{
	rc->camera_x = 2 * rc->x / (double)WIDTH - 1;
	rc->ray_dir_x = game->dir_x + game->plane_x * (rc->camera_x);
	rc->ray_dir_y = game->dir_y + game->plane_y * (rc->camera_x);
}
