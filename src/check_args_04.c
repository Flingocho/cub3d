/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:26:36 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 18:42:56 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	assign_colors_2(t_vars *vars, char **temp, char **temp2)
{
	vars->colors->c_r = ft_atoi(temp[0]);
	vars->colors->c_g = ft_atoi(temp[1]);
	vars->colors->c_b = ft_atoi(temp[2]);
	vars->colors->f_r = ft_atoi(temp2[0]);
	vars->colors->f_g = ft_atoi(temp2[1]);
	vars->colors->f_b = ft_atoi(temp2[2]);
	vars->colors->c_hex = (vars->colors->c_r << 16)
		| (vars->colors->c_g << 8) | (vars->colors->c_b);
	vars->colors->f_hex = (vars->colors->f_r << 16)
		| (vars->colors->f_g << 8) | (vars->colors->f_b);
}

void	assign_colors(t_vars *vars)
{
	int		i;
	char	**temp;
	char	**temp2;

	i = 0;
	temp = ft_split(vars->colors->c, ',');
	if (!temp)
		return (perror("malloc"), exit(1));
	while (temp[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	i = 0;
	temp2 = ft_split(vars->colors->f, ',');
	if (!temp2)
		return (perror("malloc"), exit(1));
	while (temp2[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	assign_colors_2(vars, temp, temp2);
	free_char_matrix(temp);
	free_char_matrix(temp2);
}
