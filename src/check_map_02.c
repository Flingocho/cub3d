/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:58:08 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 11:58:15 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_start_n(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = -1;
	vars->game->plane_x = 0.66;
	vars->game->plane_y = 0;
}

static void	set_start_s(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = 1;
	vars->game->plane_x = -0.66;
	vars->game->plane_y = 0;
}

static void	set_start_e(t_vars *vars)
{
	vars->game->dir_x = 1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = 0.66;
}

static void	set_start_w(t_vars *vars)
{
	vars->game->dir_x = -1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = -0.66;
}

int	check_valid_charset(t_vars *vars, char c, int i, int j)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || (BONUS && c == 'D'))
	{
		if (!(c == '1' || c == '0' || c == ' ' || (BONUS && c == 'D')))
		{
			vars->map[i][j] = '0';
			vars->player->start_orientation = (c);
			vars->game->player_x = j + 0.5;
			vars->game->player_y = i + 0.5;
			vars->player->x_start = i;
			vars->player->y_start = j;
			if (c == 'N')
				set_start_n(vars);
			else if (c == 'S')
				set_start_s(vars);
			else if (c == 'E')
				set_start_e(vars);
			else if (c == 'W')
				set_start_w(vars);
		}
		return (OK);
	}
	return (ERROR);
}
