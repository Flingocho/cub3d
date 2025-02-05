/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:50:03 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/05 12:02:45 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_valid_charset(t_vars *vars, char c, int i, int j)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
	{
		if (!(c == '1' || c == '0' || c == ' '))
		{
			vars->map[i][j] = '0';
			vars->player->start_orientation = (c);
			vars->game->player_x = j + 0.5;
			vars->game->player_y = i + 0.5;
			if (c == 'N')
			{
				vars->game->dir_x = 0;
				vars->game->dir_y = -1;
				vars->game->plane_x = 0.66;
				vars->game->plane_y = 0;
			}
			else if (c == 'S')
			{
				vars->game->dir_x = 0;
				vars->game->dir_y = 1;
				vars->game->plane_x = -0.66;
				vars->game->plane_y = 0;
			}
			else if (c == 'E')
			{
				vars->game->dir_x = 1;
				vars->game->dir_y = 0;
				vars->game->plane_x = 0;
				vars->game->plane_y = 0.66;
			}
			else if (c == 'W')
			{
				vars->game->dir_x = -1;
				vars->game->dir_y = 0;
				vars->game->plane_x = 0;
				vars->game->plane_y = -0.66;
			}
		}
		return (OK);
	}
	return (ERROR);
}

static void set_matrix_int(t_vars *vars)
{
    int i;
    int j;
    int row_length;

    i = 0;
    while (i < vars->game->map_height)
    {
        row_length = ft_strlen(vars->map[i]);
        j = 0;
        while (j < vars->game->map_width)
        {
            if (j < row_length && vars->map[i][j] == '0')
                vars->game->world_map[i][j] = 0;
            else
                vars->game->world_map[i][j] = 1;
            j++;
        }
        i++;
    }
}

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
	// floodfill
	i = 0;
	vars->game->world_map = calloc(vars->game->map_height, sizeof(int *)); // proteger
	while(i < vars->game->map_height)
		vars->game->world_map[i++] = calloc(vars->game->map_width, sizeof(int)); // proteger
	set_matrix_int(vars);
	return (OK);
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
	if(map_dimensions(vars) == ERROR)
		return(ERROR);
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
	close(vars->map_path_fd);
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
