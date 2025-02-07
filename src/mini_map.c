/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:24:44 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 12:35:11 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void    draw_square(t_game *game, int x, int y, int color)
{
    int i, j;
    int start_x = MAP_OFFSET + x * TILE_SIZE;
    int start_y = MAP_OFFSET + y * TILE_SIZE;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i, color);
            j++;
        }
        i++;
    }
}

static void draw_cells(t_game *game, int start_x, int start_y, int end_x, int end_y)
{
    int y = start_y;
    while (y <= end_y)
    {
        int x = start_x;
        while (x <= end_x)
        {
            int color;
            if (game->world_map[y][x] == 1)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            draw_square(game, x - start_x, y - start_y, color);
            x++;
        }
        y++;
    }
}


static void clamp_minimap_bounds(t_game *game, int *start_x, int *start_y, int *end_x, int *end_y)
{
    if (*start_x < 0)
        *start_x = 0;
    if (*start_y < 0)
        *start_y = 0;
    if (*end_x >= game->map_width)
        *end_x = game->map_width - 1;
    if (*end_y >= game->map_height)
        *end_y = game->map_height - 1;
}

void draw_minimap(t_game *game)
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;

    start_x = (int)(game->player_x) - MINIMAP_RADIUS;
    start_y = (int)(game->player_y) - MINIMAP_RADIUS;
    end_x = (int)(game->player_x) + MINIMAP_RADIUS;
    end_y = (int)(game->player_y) + MINIMAP_RADIUS;
    clamp_minimap_bounds(game, &start_x, &start_y, &end_x, &end_y);
    draw_cells(game, start_x, start_y, end_x, end_y);
    draw_square(game, game->player_x - start_x, game->player_y - start_y, 0xFF0000);
}
