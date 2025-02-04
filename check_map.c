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

void	read_fd_file(t_vars *vars)
{
	vars->reader = ft_calloc(sizeof(char *), BUFF_SIZE);
	if (!vars->reader)
		return (perror("malloc"), close(vars->map_path_fd),
			free(vars->map_path), exit(ERROR));
	vars->bytes_read = read(vars->map_path_fd, vars->reader, BUFF_SIZE);
	if (vars->bytes_read == -1 || vars->reader[BUFF_SIZE - 1] != '\0')
		return (perror("read"), close(vars->map_path_fd), free(vars->map_path),
			exit(ERROR));
	vars->file = ft_split(vars->reader, '\n');
	if (!vars->file)
		(perror("read"), exit(ERROR));
	close(vars->map_path_fd);
	free(vars->reader);
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
