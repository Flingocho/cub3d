/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:46:24 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 12:51:21 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	perform_dda(t_game *game, int *mapX, int *mapY, double *sideDistX,
		double *sideDistY, double deltaDistX, double deltaDistY, int *stepX,
		int *stepY, int *side, int *hit)
{
	while (!(*hit))
	{
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += deltaDistX;
			*mapX += *stepX;
			*side = 0;
		}
		else
		{
			*sideDistY += deltaDistY;
			*mapY += *stepY;
			*side = 1;
		}
		if (game->world_map[*mapY][*mapX] != 0
			&& game->world_map[*mapY][*mapX] != 3)
			*hit = 1;
	}
}

void	process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	perform_dda(game, &rc->mapX, &rc->mapY, &rc->sideDistX, &rc->sideDistY,
			rc->deltaDistX, rc->deltaDistY, &rc->stepX, &rc->stepY, &rc->side,
			&rc->hit);
	render_column(game, vars, rc);
}

void	initialize_step_and_sidedist(t_game *game, t_ray_cast *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (game->player_x - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - game->player_x) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (game->player_y - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - game->player_y) * rc->deltaDistY;
	}
}

void	initialize_ray_position(t_game *game, double rayDirX, double rayDirY,
		int *mapX, int *mapY, double *deltaDistX, double *deltaDistY)
{
	*mapX = (int)game->player_x;
	*mapY = (int)game->player_y;
	*deltaDistX = fabs(1 / rayDirX);
	*deltaDistY = fabs(1 / rayDirY);
}

void	calculate_ray_direction(t_game *game, int x, double *rayDirX,
		double *rayDirY, double *cameraX)
{
	*cameraX = 2 * x / (double)WIDTH - 1;
	*rayDirX = game->dir_x + game->plane_x * (*cameraX);
	*rayDirY = game->dir_y + game->plane_y * (*cameraX);
}
