/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:47:48 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/05 16:21:45 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_args_number(int argc)
{
	if (argc == 2)
		return (OK);
	return (ERROR);
}

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
