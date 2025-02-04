/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:03 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/04 18:34:14 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_valid_charset(t_vars *vars, char c, int i, int j)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
	{
		if (!(c == '1' || c == '0' || c == ' '))
		{
			vars->map[i][j] = '0';
			vars->player->start_orientation = (c);
			vars->player->x_start = i;
			vars->player->y_start = j;
		}
		return (OK);
	}
	return (ERROR);
}

int	check_map_valid(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
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
	return (OK);
}

void	read_fd_file(t_vars *vars)
{
	vars->buffer = ft_calloc(sizeof(char *), BUFF_SIZE);
	if (!vars->buffer)
		return (perror("malloc"), close(vars->map_path_fd),
			free(vars->map_path), exit(ERROR));
	vars->bytes_read = read(vars->map_path_fd, vars->buffer, BUFF_SIZE);
	if (vars->bytes_read == -1 || vars->buffer[BUFF_SIZE - 1] != '\0')
		return (perror("read"), close(vars->map_path_fd), free(vars->map_path),
			exit(ERROR));
	vars->file = ft_split(vars->buffer, '\n');
	if (!vars->file)
		(perror("read"), exit(ERROR));
	close(vars->map_path_fd); //nos gusta limpiar aqui o limpiamos todo en el cleaner?
	free(vars->buffer);
	parse_file(vars);
}

int	assign_map_path(char *path, t_vars *vars)
{
	vars->map_path = ft_strdup(path);
	if (!vars->map_path)
		return (perror("malloc"), close(vars->map_path_fd), exit(ERROR), ERROR);
	return (OK);
}

int	check_map_exists(char *path, t_vars *vars)
{
	vars->map_path_fd = open(path, O_RDONLY);
	if (vars->map_path_fd < 0)
		return (perror("open"), exit(ERROR), ERROR);
	return (OK);
}
