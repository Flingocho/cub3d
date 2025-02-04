/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:26:36 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/04 18:44:17 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_value(t_vars *vars, char *value)
{
    printf("%s\n", value);
	if (value[0] == '1')
	{
		printf("MAP STARTING\n");
		return (ERROR);
	}
	if (ft_strncmp(value, "NO", 2) == OK)
		vars->paths->no = ft_strdup(value + 3);
	else if (ft_strncmp(value, "SO", 2) == OK)
		vars->paths->so = ft_strdup(value + 3);
	else if (ft_strncmp(value, "WE", 2) == OK)
		vars->paths->we = ft_strdup(value + 3);
	else if (ft_strncmp(value, "EA", 2) == OK)
		vars->paths->ea = ft_strdup(value + 3);
    else if (ft_strncmp(value, "f", 1) == OK)
		vars->paths->f = ft_strdup(value + 2);
    else if (ft_strncmp(value, "c", 1) == OK)
		vars->paths->c = ft_strdup(value + 2);
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
			if (set_value(vars, &vars->file[i][j]) == ERROR)
				break ;
		i++;
	}
}
