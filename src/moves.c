/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:49 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/11 13:43:07 by jvidal-t         ###   ########.fr       */
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
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x + game->dir_x * MOVE_SPEED;
	new_y = game->player_y + game->dir_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->dir_x < 0)
		offset_x = -0.2;
	if (game->dir_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x - game->dir_x * MOVE_SPEED;
	new_y = game->player_y - game->dir_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->dir_x < 0)
		offset_x = 0.2;
	if (game->dir_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x + game->plane_x * MOVE_SPEED;
	new_y = game->player_y + game->plane_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->plane_x < 0)
		offset_x = -0.2;
	if (game->plane_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x - game->plane_x * MOVE_SPEED;
	new_y = game->player_y - game->plane_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->plane_x < 0)
		offset_x = 0.2;
	if (game->plane_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}
