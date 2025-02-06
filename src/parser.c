/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:26:36 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/06 16:17:07 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	assign_colors(t_vars *vars)
{
	char	**temp;
	char	**temp2;

	temp = ft_split(vars->colors->c, ',');
	temp2 = ft_split(vars->colors->f, ',');
	vars->colors->c_r = ft_atoi(temp[0]);
	vars->colors->c_g = ft_atoi(temp[1]);
	vars->colors->c_b = ft_atoi(temp[2]);
	vars->colors->f_r = ft_atoi(temp2[0]);
	vars->colors->f_g = ft_atoi(temp2[1]);
	vars->colors->f_b = ft_atoi(temp2[2]);
	free_char_matrix(temp);
	free_char_matrix(temp2);
	vars->colors->c_hex = (vars->colors->c_r << 16) | (vars->colors->c_g << 8) | (vars->colors->c_b);
	vars->colors->f_hex = (vars->colors->f_r << 16) | (vars->colors->f_g << 8) | (vars->colors->f_b);
}

int	set_value(t_vars *vars, char *value)
{	
	if (value[0] == '1')
		return (2);
	else if (ft_strncmp(value, "NO", 2) == OK)
	{
		vars->paths->no = ft_strdup(value + 3);
		if (!vars->paths->no)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "SO", 2) == OK)
	{
		vars->paths->so = ft_strdup(value + 3);
		if (!vars->paths->so)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "WE", 2) == OK)
	{
		vars->paths->we = ft_strdup(value + 3);
		if (!vars->paths->we)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "EA", 2) == OK)
	{
		vars->paths->ea = ft_strdup(value + 3);
		if (!vars->paths->ea)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "F", 1) == OK)
	{
		vars->colors->f = ft_strdup(value + 2);
		if (!vars->colors->f)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "C", 1) == OK)
	{
		vars->colors->c = ft_strdup(value + 2);
		if (!vars->colors->c)
			return (perror("malloc"), ERROR);
	}
	return (OK);
}

void	parse_file(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->file[i])
	{
		j = 0;
		while (vars->file[i][j] != '\0' && isspace(vars->file[i][j]))
			j++;
		if (vars->file[i][j] != '\0')
			if (set_value(vars, &vars->file[i][j]) == 2)
			{
				assign_colors(vars);
				vars->map = &vars->file[i];
				break ;
			}
		i++;
	}
}
