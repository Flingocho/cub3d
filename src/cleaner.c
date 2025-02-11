/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:47:10 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 17:50:33 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_exit(t_vars *vars)
{
	mlx_loop_end(vars->game->mlx);
	mlx_destroy_image(vars->game->mlx, vars->game->img.img);
	free_textures(vars->game);
	mlx_destroy_window(vars->game->mlx, vars->game->win);
	mlx_destroy_display(vars->game->mlx);
	free(vars->game->mlx);
	free_char_matrix(vars->file);
	free_int_matrix(vars, vars->game->world_map);
	free_paths(vars);
	free_colors(vars);
	free(vars->paths);
	free(vars->player);
	free(vars->colors);
	free(vars->game);
	free(vars);
}
