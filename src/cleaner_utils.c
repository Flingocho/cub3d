/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:47:49 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 14:06:58 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_char_matrix(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

void	free_int_matrix(t_vars *vars, int **mtx)
{
	int	i;

	i = 0;
	while (i < vars->game->map_height)
		free(mtx[i++]);
	free(mtx);
}

void	free_paths(t_vars *vars)
{
	free(vars->paths->no);
	free(vars->paths->so);
	free(vars->paths->we);
	free(vars->paths->ea);
}

void	free_colors(t_vars *vars)
{
	free(vars->colors->c);
	free(vars->colors->f);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	while (BONUS && i < 8)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}
