/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:46:23 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 12:43:42 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	t_img textures[8]; // Array de texturas (NORTE, SUR, ESTE, OESTE)
	int **world_map;   // Mapa leído del archivo

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

	int map_width;  // Ancho del mapa
	int map_height; // Alto del mapa

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
	int x; // Coordenada X del rayo
	int			hit;
	// Indicador si el rayo ha colisionado con una pared (1 = sí, 0 = no)
	int			side;
	// Indica si el rayo tocó una pared en el eje X (0) o en el Y (1)
	double cameraX; // Coordenada X en el espacio de cámara
	double rayDirX; // Dirección del rayo en el eje X
	double rayDirY; // Dirección del rayo en el eje Y
	int mapX;       // Posición X en el mapa del mundo
	int mapY;       // Posición Y en el mapa del mundo
	double		deltaDistX;
	// Distancia entre el rayo y las líneas del mapa en el eje X
	double		deltaDistY;
	// Distancia entre el rayo y las líneas del mapa en el eje Y
	double		sideDistX;
	// Distancia entre el rayo y el borde más cercano en el eje X
	double		sideDistY;
	// Distancia entre el rayo y el borde más cercano en el eje Y
	int stepX; // Dirección del paso en el eje X (-1 o 1)
	int stepY; // Dirección del paso en el eje Y (-1 o 1)
}				t_ray_cast;

typedef struct s_ray_cast_draw
{
	double perpWallDist; // Distancia perpendicular entre el rayo y la pared
	double wallX;        // Coordenada X del lugar de impacto en la pared
	int y;               // Coordenada Y para dibujar la pared
	int lineHeight;      // Altura de la pared a dibujar
	int drawStart;       // Coordenada Y de inicio para dibujar la pared
	int drawEnd;         // Coordenada Y final para dibujar la pared
	int texNum;          // Número de la textura a usar para la pared
	int texX;            // Coordenada X de la textura
	int d;               // Distancia utilizada para calcular la textura
	int texY;            // Coordenada Y de la textura
	int color;           // Color del píxel actual
}				t_ray_cast_draw;

#endif