/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:36:30 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 16:14:21 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	f_fill(t_vars *vars, int row, int col, int size)
{
	int	row_length;

	if (row < 0 || row >= size)
		return (ERROR);
	row_length = ft_strlen(vars->map[row]);
	if (col < 0 || col >= row_length)
		return (ERROR);
	if (vars->map[row][col] == '1' || vars->map[row][col] == ' '
		|| vars->map[row][col] == 'F')
		return (OK);
	vars->map[row][col] = 'F';
	if (f_fill(vars, row - 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row + 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col - 1, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col + 1, size) == ERROR)
		return (ERROR);
	return (OK);
}

static int	flood_fill(t_vars *vars, int size)
{
	return (f_fill(vars, vars->player->x_start, vars->player->y_start, size));
}

int	check_flood(t_vars *vars)
{
	int	size;

	size = 0;
	if (vars->player->x_start < 0 || vars->player->y_start < 0)
		return (ERROR);
	while (vars->map[size])
		size++;
	return (flood_fill(vars, size));
}
