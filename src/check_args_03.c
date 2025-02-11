/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:26:36 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 18:26:32 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_value_03(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "F", 1) == OK)
	{
		if (vars->colors->f)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->f = ft_strtrim(value + 2, " \t");
		if (!vars->colors->f)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "C", 1) == OK)
	{
		if (vars->colors->c)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->c = ft_strtrim(value + 2, " \t");
		if (!vars->colors->c)
			return (perror("malloc"), ERROR);
	}
	return (OK);
}

static int	set_value_02(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "WE", 2) == OK)
	{
		if (vars->paths->we)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->we = ft_strtrim(value + 3, " \t");
		if (!vars->paths->we)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "EA", 2) == OK)
	{
		if (vars->paths->ea)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->ea = ft_strtrim(value + 3, " \t");
		if (!vars->paths->ea)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_03(vars, value) == ERROR)
		return (ERROR);
	return (OK);
}

static int	set_value(t_vars *vars, char *value)
{
	if (value[0] == '1')
		return (2);
	else if (ft_strncmp(value, "NO", 2) == OK)
	{
		if (vars->paths->no)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->no = ft_strtrim(value + 3, " \t");
		if (!vars->paths->no)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "SO", 2) == OK)
	{
		if (vars->paths->so)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->so = ft_strtrim(value + 3, " \t");
		if (!vars->paths->so)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_02(vars, value) == ERROR)
		return (ERROR);
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
		{
			if (set_value(vars, &vars->file[i][j]) == 2)
			{
				assign_colors(vars);
				vars->map = &vars->file[i];
				break ;
			}
		}
		i++;
	}
}
