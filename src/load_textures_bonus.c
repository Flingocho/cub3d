/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:01:47 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/11 18:07:11 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	door1(t_game *game)
{
	char	path[20];

	ft_strcpy(path, "textures/door_1.xpm");
	game->textures[4].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[4].width, &game->textures[4].height);
	if (!game->textures[4].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[4].addr = mlx_get_data_addr(game->textures[4].img,
			&game->textures[4].bpp, &game->textures[4].line_length,
			&game->textures[4].endian);
}

static void	door2(t_game *game)
{
	char	path[20];

	ft_strcpy(path, "textures/door_2.xpm");
	game->textures[5].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[5].width, &game->textures[5].height);
	if (!game->textures[5].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[5].addr = mlx_get_data_addr(game->textures[5].img,
			&game->textures[5].bpp, &game->textures[5].line_length,
			&game->textures[5].endian);
}

static void	door3(t_game *game)
{
	char	path[20];

	ft_strcpy(path, "textures/door_3.xpm");
	game->textures[6].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[6].width, &game->textures[6].height);
	if (!game->textures[6].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[6].addr = mlx_get_data_addr(game->textures[6].img,
			&game->textures[6].bpp, &game->textures[6].line_length,
			&game->textures[6].endian);
}

static void	door4(t_game *game)
{
	char	path[20];

	ft_strcpy(path, "textures/door_4.xpm");
	game->textures[7].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[7].width, &game->textures[7].height);
	if (!game->textures[7].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[7].addr = mlx_get_data_addr(game->textures[7].img,
			&game->textures[7].bpp, &game->textures[7].line_length,
			&game->textures[7].endian);
}

int	load_textures_bonus(t_vars *vars)
{
	door1(vars->game);
	door2(vars->game);
	door3(vars->game);
	door4(vars->game);
	return (OK);
}
