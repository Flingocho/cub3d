/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:42:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/04 18:44:01 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# define BUFF_SIZE 999999
# define OK 0
# define ERROR 1

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	char	*f;
	char	*c;
}			t_paths;

typedef struct s_vars
{
	int		map_path_fd;
	int		bytes_read;
	t_paths	*paths;
	char	*map_path;
	char	*reader;
	char	**file;
	char	**map;

}			t_vars;

// check_args.c
int			check_args(int argc, char *argv[], t_vars *vars);

// check_map.c
int			check_map_exists(char *path, t_vars *vars);
int			assign_map_path(char *path, t_vars *vars);
void		read_fd_file(t_vars *vars);

// parser.c
void		parse_file(t_vars *vars);

#endif