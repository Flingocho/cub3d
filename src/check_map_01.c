/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:03 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/07 12:00:15 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_matrix_int(t_vars *vars)
{
	int	i;
	int	j;
	int	row_length;

	i = 0;
	while (i < vars->game->map_height)
	{
		row_length = ft_strlen(vars->map[i]);
		j = 0;
		while (j < vars->game->map_width)
		{
			if (j < row_length && vars->map[i][j] == '0')
				vars->game->world_map[i][j] = 0;
			else if (j < row_length && vars->map[i][j] == 'D')
				vars->game->world_map[i][j] = 2;
			else
				vars->game->world_map[i][j] = 1;
			j++;
		}
		i++;
	}
}

// OJO Proteger Callocs
static int	map_dimensions(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if (vars->game->map_width < ft_strlen(vars->map[i]))
			vars->game->map_width = ft_strlen(vars->map[i]);
		i++;
	}
	vars->game->map_height = i;
	i = 0;
	vars->game->world_map = calloc(vars->game->map_height, sizeof(int *));
	while (i < vars->game->map_height)
		vars->game->world_map[i++] = calloc(vars->game->map_width, sizeof(int));
	set_matrix_int(vars);
	if (check_flood(vars) == ERROR)
		return (printf("Gestionar esta salida!!\n"), exit(ERROR), ERROR);
	return (OK);
}

static int	check_repeated_position(char **map)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				counter++;
			j++;
		}
		i++;
	}
	if (counter == 1)
		return (OK);
	printf("MAP INVALID\n");
	return (ERROR);
}

// OJO Gestionar salidas
int	check_map_valid(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	if (check_repeated_position(vars->map) == ERROR)
		return (printf("Gestionar esta salida!!\n"), ERROR);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (check_valid_charset(vars, vars->map[i][j], i, j) == ERROR)
				return (perror("charset"), ERROR);
			if (vars->map[i][j] == ' ')
				vars->map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (map_dimensions(vars) == ERROR)
		return (ERROR);
	return (OK);
}
