/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:32:08 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/05 17:32:09 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	north(t_vars *vars)
{
	vars->game->textures[0].img = mlx_xpm_file_to_image(vars->game->mlx,
			vars->paths->no, &vars->game->textures[0].width,
			&vars->game->textures[0].height);
	if (!vars->game->textures[0].img)
	{
		printf("Error: No se pudo cargar la textura \'%s\'\n", vars->paths->no);
		exit(0);
	}
	vars->game->textures[0].addr = mlx_get_data_addr(vars->game->textures[0].img,
			&vars->game->textures[0].bpp, &vars->game->textures[0].line_length,
			&vars->game->textures[0].endian);
}
static void	south(t_vars *vars)
{
	vars->game->textures[1].img = mlx_xpm_file_to_image(vars->game->mlx,
			vars->paths->so, &vars->game->textures[1].width,
			&vars->game->textures[1].height);
	if (!vars->game->textures[1].img)
	{
		printf("Error: No se pudo car2gar la textura %s\n", vars->paths->so);
		exit(0);
	}
	vars->game->textures[1].addr = mlx_get_data_addr(vars->game->textures[1].img,
			&vars->game->textures[1].bpp, &vars->game->textures[1].line_length,
			&vars->game->textures[1].endian);
}
static void	east(t_vars *vars)
{
	vars->game->textures[2].img = mlx_xpm_file_to_image(vars->game->mlx,
			vars->paths->ea, &vars->game->textures[2].width,
			&vars->game->textures[2].height);
	if (!vars->game->textures[2].img)
	{
		printf("Error: No se pudo 3cargar la textura %s\n", vars->paths->ea);
		exit(0);
	}
	vars->game->textures[2].addr = mlx_get_data_addr(vars->game->textures[2].img,
			&vars->game->textures[2].bpp, &vars->game->textures[2].line_length,
			&vars->game->textures[2].endian);
}
static void	west(t_vars *vars)
{
	vars->game->textures[3].img = mlx_xpm_file_to_image(vars->game->mlx,
			vars->paths->we, &vars->game->textures[3].width,
			&vars->game->textures[3].height);
	if (!vars->game->textures[3].img)
	{
		printf("Error: No se pudo4 cargar la textura %s\n", vars->paths->we);
		exit(0);
	}
	vars->game->textures[3].addr = mlx_get_data_addr(vars->game->textures[3].img,
			&vars->game->textures[3].bpp, &vars->game->textures[3].line_length,
			&vars->game->textures[3].endian);
}

int	load_textures(t_vars *vars)
{
	north(vars);
	south(vars);
	east(vars);
	west(vars);
	return (OK);
}

void	init_vars(t_vars **vars)
{
	// PROTEGEME MAMAÑEMA
	*vars = ft_calloc(1, sizeof(t_vars));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
	(*vars)->player = ft_calloc(1, sizeof(t_player));
	(*vars)->game = ft_calloc(1, sizeof(t_game));
	(*vars)->game->mlx = mlx_init();
	(*vars)->game->win = mlx_new_window((*vars)->game->mlx, WIDTH, HEIGHT,
			"Cub3d");
	(*vars)->game->img.img = mlx_new_image((*vars)->game->mlx, WIDTH, HEIGHT);
	(*vars)->game->img.addr = mlx_get_data_addr((*vars)->game->img.img,
			&(*vars)->game->img.bpp, &(*vars)->game->img.line_length,
			&(*vars)->game->img.endian);
}
