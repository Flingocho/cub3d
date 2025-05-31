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

/**
 * @brief Initialize player direction and camera plane for north orientation
 * 
 * When the player starts facing north ('N'), this function sets the initial
 * direction vector (0,-1) and camera plane (0.66,0) for raycasting.
 * 
 * @param vars The main program structure
 */
static void	set_start_n(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = -1;
	vars->game->plane_x = 0.66;
	vars->game->plane_y = 0;
}

/**
 * @brief Initialize player direction and camera plane for south orientation
 * 
 * When the player starts facing south ('S'), this function sets the initial
 * direction vector (0,1) and camera plane (-0.66,0) for raycasting.
 * 
 * @param vars The main program structure
 */
static void	set_start_s(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = 1;
	vars->game->plane_x = -0.66;
	vars->game->plane_y = 0;
}

/**
 * @brief Initialize player direction and camera plane for east orientation
 * 
 * When the player starts facing east ('E'), this function sets the initial
 * direction vector (1,0) and camera plane (0,0.66) for raycasting.
 * 
 * @param vars The main program structure
 */
static void	set_start_e(t_vars *vars)
{
	vars->game->dir_x = 1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = 0.66;
}

/**
 * @brief Initialize player direction and camera plane for west orientation
 * 
 * When the player starts facing west ('W'), this function sets the initial
 * direction vector (-1,0) and camera plane (0,-0.66) for raycasting.
 * 
 * @param vars The main program structure
 */
static void	set_start_w(t_vars *vars)
{
	vars->game->dir_x = -1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = -0.66;
}

/**
 * @brief Validate map characters and set player position if found
 * 
 * This function checks if a character is valid for the map and handles player
 * position markers (N, S, E, W) by:
 * 1. Setting the player's start position and orientation
 * 2. Converting the marker to '0' (empty space) in the map
 * 3. Initializing direction vector and camera plane based on orientation
 * 
 * @param vars The main program structure
 * @param c Character to check
 * @param i Row index in the map
 * @param j Column index in the map
 * @return OK if character is valid, ERROR otherwise
 */
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
