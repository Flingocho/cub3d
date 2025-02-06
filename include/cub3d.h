/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:42:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/06 11:58:36 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# define BUFF_SIZE 999999
# define OK 0
# define ERROR 1

# include "../libft/include/libft.h"
# include "mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 960
# define MOVE_SPEED 0.15
# define ROT_SPEED 0.05

# define TILE_SIZE 10  // Tamaño de cada celda en el minimapa
# define MAP_OFFSET 10  // Margen del minimapa en pantalla
#define MINIMAP_RADIUS 5 // Radio del minimapa (5x5 alrededor del jugador)

# define LOADING01 "Loading Cub3D... If you can read this, your reality is about to get shattered."
# define LOADING02 "Spinning up the polygons... hope your CPU survived 1996."
# define LOADING03 "Solving integrals, tracing rays, bending light... all so you can walk in a straight line."
# define LOADING04 "Assembling your 3D world... one glitch at a time."
# define LOADING05 "Simulating complex physics so you can stare at a wall for 10 minutes."
# define LOADING06 "Ray tracing equations so advanced that even Einstein would say, 'Just play Doom, bro'."
# define LOADING07 "This simulation required thousands of calculations per second. Your projects is still waiting."
# define LOADING08 "Really, Why walk around in this empty world when you could be finishing that project you keep avoiding?"
# define LOADING09 "Last chance, Go away!"
# define LOADING10 "OK... Welcome to our Cub3D, by jvidal-t and mrubal-c."

// Estructura para la imagen en MLX

typedef struct s_img
{
	void *img;       // Puntero a la imagen en MiniLibX
	char *addr;      // Dirección de memoria de la imagen
	int width;       // Ancho de la imagen
	int height;      // Alto de la imagen
	int bpp;         // Bits por píxel
	int line_length; // Longitud de cada línea en bytes
	int endian;      // Endianness de la imagen
}				t_img;

typedef enum e_orientation
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}				t_orientation;

// Estructura principal del juego
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;

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
	int			key_left;
	int			key_right;

	int **world_map; // Mapa leído del archivo
	int map_width;   // Ancho del mapa
	int map_height;  // Alto del mapa

	t_img textures[4]; // Array de texturas (NORTE, SUR, ESTE, OESTE)
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
	void *mlx; // dejamos estas aqui dentro para q no sea un coñazo?
	void *win; // o las metemos con todo lo de mlx en otra struct?

	int			map_path_fd;
	int			bytes_read;

	char		*map_path;
	char		*buffer;
	char		**file;
	char		**map;

	t_player	*player;
	t_paths		*paths;
	t_colors	*colors;
	t_game		*game;

}				t_vars;

// init_vars.c
void			init_vars(t_vars **vars);
int				load_textures(t_vars *vars);

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
void			free_char_matrix(char **mtx);

// rc.c
int				key_press(int key, t_vars *vars);
int				key_release(int key, t_game *game);
int				close_window(t_vars *vars);
int				render(t_vars *vars);
int				parse_map_file(const char *filename, t_game *game);

#endif