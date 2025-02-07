/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:15:00 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 13:40:51 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}

static void	manage_door(t_game *game)
{
	int	playerX;
	int	playerY;

	playerX = (int)game->player_x;
	playerY = (int)game->player_y;
	if (game->door_cooldown > 0)
		return ;
	if (game->world_map[playerY][playerX + 1] == 2)
		game->world_map[playerY][playerX + 1] = 3;
	else if (game->world_map[playerY][playerX - 1] == 2)
		game->world_map[playerY][playerX - 1] = 3;
	else if (game->world_map[playerY + 1][playerX] == 2)
		game->world_map[playerY + 1][playerX] = 3;
	else if (game->world_map[playerY - 1][playerX] == 2)
		game->world_map[playerY - 1][playerX] = 3;
	else if (game->world_map[playerY][playerX + 1] == 3)
		game->world_map[playerY][playerX + 1] = 2;
	else if (game->world_map[playerY][playerX - 1] == 3)
		game->world_map[playerY][playerX - 1] = 2;
	else if (game->world_map[playerY + 1][playerX] == 3)
		game->world_map[playerY + 1][playerX] = 2;
	else if (game->world_map[playerY - 1][playerX] == 3)
		game->world_map[playerY - 1][playerX] = 2;
	game->door_cooldown = 5;
}

void	update_movement(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_d)
		move_right(game);
	if (game->key_a)
		move_left(game);
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
	if (BONUS && game->key_e)
		manage_door(game);
}

int	key_press(int key, t_vars *vars)
{
	if (key == 65307)
		close_window(vars);
	if (key == 119)
		vars->game->key_w = 1;
	if (key == 115)
		vars->game->key_s = 1;
	if (key == 97)
		vars->game->key_a = 1;
	if (key == 100)
		vars->game->key_d = 1;
	if (key == 65361)
		vars->game->key_left = 1;
	if (key == 65363)
		vars->game->key_right = 1;
	if (BONUS && key == 101)
		vars->game->key_e = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->key_w = 0;
	if (key == 115)
		game->key_s = 0;
	if (key == 97)
		game->key_a = 0;
	if (key == 100)
		game->key_d = 0;
	if (key == 65361)
		game->key_left = 0;
	if (key == 65363)
		game->key_right = 0;
	if (BONUS && key == 101)
		game->key_e = 0;
	return (0);
}
