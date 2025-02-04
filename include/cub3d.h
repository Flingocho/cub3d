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

typedef struct s_player
{
	char		start_orientation;
	int			x_start;
	int			y_start;
}				t_player;

typedef struct s_colors
{
	char		*f;
	char		*c;
	//aqui es donde faltan los int f_r int f_g... etc
}				t_colors;

typedef struct s_paths
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_paths;

typedef struct s_vars
{
	void		*mlx; //dejamos estas aqui dentro para q no sea un coñazo?
	void		*win; //o las metemos con todo lo de mlx en otra struct?

	int			map_path_fd;
	int			bytes_read;

	char		*map_path;
	char		*buffer;
	char		**file;
	char		**map;

	t_player	*player;
	t_paths		*paths;
	t_colors	*colors;

}				t_vars;

// init_vars.c
void			init_vars(t_vars **vars);

// check_args.c
int				check_args(int argc, char *argv[], t_vars *vars);

// check_map.c
int				check_map_exists(char *path, t_vars *vars);
int				assign_map_path(char *path, t_vars *vars);
void			read_fd_file(t_vars *vars);
int				check_map_valid(t_vars *vars);

// parser.c
void			parse_file(t_vars *vars);

// cleaner.c
void			clean_exit(t_vars *vars);

#endif