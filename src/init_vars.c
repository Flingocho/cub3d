/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:32:08 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/07 09:40:35 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_game_values(t_vars *vars)
{
	vars->game->player_x = 0;
	vars->game->player_y = 0;
	vars->game->dir_x = 0;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = 0;
	vars->game->key_w = 0;
	vars->game->key_a = 0;
	vars->game->key_s = 0;
	vars->game->key_d = 0;
	vars->game->key_e = 0;
	vars->game->key_left = 0;
	vars->game->key_right = 0;
	vars->game->door_cooldown = 0;
	vars->game->map_width = 0;
	vars->game->map_height = 0;
}

// OJO PROTEGEME MAMAÑEMA
static void	init_game(t_vars *vars)
{
	vars->game->mlx = mlx_init();
	vars->game->win = mlx_new_window(vars->game->mlx, WIDTH, HEIGHT, "Cub3d");
	vars->game->img.img = mlx_new_image(vars->game->mlx, WIDTH, HEIGHT);
	vars->game->img.addr = mlx_get_data_addr(vars->game->img.img,
			&vars->game->img.bpp, &vars->game->img.line_length,
			&vars->game->img.endian);
	vars->game->world_map = NULL;
	init_game_values(vars);
}

// OJO PROTEGEME MAMAÑEMA
void	init_vars(t_vars **vars)
{
	*vars = ft_calloc(1, sizeof(t_vars));
	(*vars)->game = ft_calloc(1, sizeof(t_game));
	(*vars)->player = ft_calloc(1, sizeof(t_player));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
	(*vars)->map_path_fd = 0;
	(*vars)->bytes_read = 0;
	(*vars)->map_path = NULL;
	(*vars)->buffer = NULL;
	(*vars)->file = NULL;
	(*vars)->map = NULL;
	init_game((*vars));
}
