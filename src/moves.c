/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:49 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 12:39:43 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	move_forward(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	newX = game->player_x + game->dir_x * MOVE_SPEED;
	newY = game->player_y + game->dir_y * MOVE_SPEED;
	offsetX = 0.2;
	offsetY = 0.2;
	if (game->dir_x < 0)
		offsetX = -0.2;
	if (game->dir_y < 0)
		offsetY = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 3)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 3)
		game->player_y = newY;
}

void	move_backward(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	newX = game->player_x - game->dir_x * MOVE_SPEED;
	newY = game->player_y - game->dir_y * MOVE_SPEED;
	offsetX = -0.2;
	offsetY = -0.2;
	if (game->dir_x < 0)
		offsetX = 0.2;
	if (game->dir_y < 0)
		offsetY = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 3)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 3)
		game->player_y = newY;
}

void	move_right(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	newX = game->player_x + game->plane_x * MOVE_SPEED;
	newY = game->player_y + game->plane_y * MOVE_SPEED;
	offsetX = 0.2;
	offsetY = 0.2;
	if (game->plane_x < 0)
		offsetX = -0.2;
	if (game->plane_y < 0)
		offsetY = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 3)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 3)
		game->player_y = newY;
}

void	move_left(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	newX = game->player_x - game->plane_x * MOVE_SPEED;
	newY = game->player_y - game->plane_y * MOVE_SPEED;
	offsetX = -0.2;
	offsetY = -0.2;
	if (game->plane_x < 0)
		offsetX = 0.2;
	if (game->plane_y < 0)
		offsetY = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 3)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 3)
		game->player_y = newY;
}
