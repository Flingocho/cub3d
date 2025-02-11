/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:24:44 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/11 14:15:26 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = MAP_OFFSET + x * TILE_SIZE;
	start_y = MAP_OFFSET + y * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i,
				color);
			j++;
		}
		i++;
	}
}

static void	draw_cells(t_game *game, t_minimap *vals)
{
	int	y;
	int	x;
	int	color;

	y = vals->start_y;
	while (y <= vals->end_y)
	{
		x = vals->start_x;
		while (x <= vals->end_x)
		{
			if (game->world_map[y][x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(game, x - vals->start_x, y - vals->start_y, color);
			x++;
		}
		y++;
	}
}

static void	clamp_minimap_bounds(t_game *game, t_minimap *vals)
{
	if (vals->start_x < 0)
		vals->start_x = 0;
	if (vals->start_y < 0)
		vals->start_y = 0;
	if (vals->end_x >= game->map_width)
		vals->end_x = game->map_width - 1;
	if (vals->end_y >= game->map_height)
		vals->end_y = game->map_height - 1;
}

void	draw_minimap(t_game *game)
{
	t_minimap	vals;

	vals.start_x = (int)(game->player_x) - MINIMAP_RADIUS;
	vals.start_y = (int)(game->player_y) - MINIMAP_RADIUS;
	vals.end_x = (int)(game->player_x) + MINIMAP_RADIUS;
	vals.end_y = (int)(game->player_y) + MINIMAP_RADIUS;
	clamp_minimap_bounds(game, &vals);
	draw_cells(game, &vals);
	draw_square(game, game->player_x - vals.start_x, game->player_y
		- vals.start_y, 0xFF0000);
}
