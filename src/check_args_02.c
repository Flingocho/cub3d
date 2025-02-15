/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:49:35 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/15 14:02:43 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	skip_vals_lines(char *file, int *i)
{
	while (file[*i])
	{
		while (file[*i] && file[*i] != '\n')
			(*i)++;
		if (file[*i] == '\0')
			break ;
		(*i)++;
		while (file[*i] && isspace(file[*i]))
			(*i)++;
		if (file[*i] && (file[*i] == '0' || file[*i] == '1'))
			break;
	}
	if (!file[*i])
		return (ERROR);
	return (OK);
}

static int	check_n_between_map(char *file)
{
	int	i;

	i = 0;
	if (skip_vals_lines(file, &i) == ERROR)
		return (ERROR);
	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if (file[i] == '\0')
			break ;
		i++;
		if (file[i] == '\n')
		{
			while (file[i] && (isspace(file[i]) || file[i] == '\n'))
				i++;
			if (file[i] == '\0')
				return (OK);
			else
				return (ERROR);
		}
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
	if (check_n_between_map(vars->buffer) == ERROR)
		return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
			exit(1));
	vars->file = ft_split(vars->buffer, '\n');
	if (!vars->file)
		(perror("read"), exit(ERROR));
	close(vars->map_path_fd);
	free(vars->buffer);
	parse_file(vars);
}

int	check_map_exists(char *path, t_vars *vars)
{
	vars->map_path_fd = open(path, O_RDONLY);
	if (vars->map_path_fd < 0)
		return (perror("open"), exit(ERROR), ERROR);
	return (OK);
}
