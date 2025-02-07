/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:47:48 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/07 12:00:47 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//OJO AÑADIR MENSAJE ERROR
static int	check_args_number(int argc)
{
	if (argc == 2)
		return (OK);
	return (ERROR);
}

//OJO AÑADIR MENSAJE ERROR
static int	check_argv_extension(char *argv[])
{
	int	i;

	i = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4) == OK)
		return (OK);
	return (ERROR);
}

int	check_args(int argc, char *argv[], t_vars *vars)
{
	if (check_args_number(argc) == OK && check_argv_extension(argv) == OK
		&& check_map_exists(argv[1], vars) == OK)
	{
		read_fd_file(vars);
		return (OK);
	}
	else
	{
		printf("Openning default map\n");
		assign_map_path("maps/map.cub", vars);
	}
	return (ERROR);
}
