/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:46:23 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/11 15:30:42 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef enum e_orientation
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	DOOR1 = 4,
	DOOR2 = 5,
	DOOR3 = 6,
	DOOR4 = 7
}				t_orientation;

// Estructura principal del juego
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		textures[8];
	int			**world_map;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_e;
	int			key_left;
	int			key_right;
	int			door_cooldown;
	int			map_width;
	int			map_height;

}				t_game;

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
	int			f_hex;
	int			c_hex;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
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
	t_game		*game;
	t_player	*player;
	t_paths		*paths;
	t_colors	*colors;
	int			map_path_fd;
	int			bytes_read;

	char		*map_path;
	char		*buffer;
	char		**file;
	char		**map;

}				t_vars;

typedef struct s_ray_cast
{
	int			x;
	int			hit;
	int			side;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
}				t_ray_cast;

typedef struct s_ray_cast_draw
{
	double		perp_wall_dist;
	double		wall_x;
	int			y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			tex_x;
	int			d;
	int			tex_y;
	int			color;
}				t_ray_cast_draw;

typedef struct s_minimap
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}				t_minimap;

#endif