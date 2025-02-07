/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:36:30 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/07 12:11:12 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	f_fill(t_vars *vars, int row, int col, int size)
{
	if (row < 0 || row >= size)
		return (ERROR);
	if (col < 0 || col >= (int)ft_strlen(vars->map[row]))
		return (ERROR);
	if (vars->map[row][col] == '1' || vars->map[row][col] == ' ')
		return (OK);
	if (vars->map[row][col] == 'F')
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
	return (f_fill(vars, vars->player->y_start, vars->player->x_start, size));
}

int	check_flood(t_vars *vars)
{
	int	size;

	size = 0;
	while (vars->map[size++])
		if (vars->player->x_start < 0 || vars->player->y_start < 0)
			return (ERROR);
	return (flood_fill(vars, size));
}
