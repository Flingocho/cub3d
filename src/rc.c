#include "../include/cub3d.h"

//////////////////////////////////////// .H

typedef struct s_ray_cast
{
	int x; // Coordenada X del rayo
	int		hit;
	// Indicador si el rayo ha colisionado con una pared (1 = sí, 0 = no)
	int		side;
	// Indica si el rayo tocó una pared en el eje X (0) o en el Y (1)
	double cameraX; // Coordenada X en el espacio de cámara
	double rayDirX; // Dirección del rayo en el eje X
	double rayDirY; // Dirección del rayo en el eje Y
	int mapX;       // Posición X en el mapa del mundo
	int mapY;       // Posición Y en el mapa del mundo
	double	deltaDistX;
	// Distancia entre el rayo y las líneas del mapa en el eje X
	double	deltaDistY;
	// Distancia entre el rayo y las líneas del mapa en el eje Y
	double	sideDistX;
	// Distancia entre el rayo y el borde más cercano en el eje X
	double	sideDistY;
	// Distancia entre el rayo y el borde más cercano en el eje Y
	int stepX; // Dirección del paso en el eje X (-1 o 1)
	int stepY; // Dirección del paso en el eje Y (-1 o 1)
}			t_ray_cast;

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
}			t_ray_cast_draw;

////////////////////////////////////////////

int	darken_color(int color, double distance)
{
    // Distancia a partir de la cual la niebla se aplica completamente.
    double max_distance = 5.0;
    
    // Calcula el factor de mezcla: 0.0 cuando distance es 0 y 1.0 cuando distance >= max_distance
    double fogFactor = distance / max_distance;
    if (fogFactor > 1.0)
        fogFactor = 1.0;

    // Extraer los componentes RGB del color original
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8)  & 0xFF;
    int b = color & 0xFF;

    // Define el color de la niebla. Puedes cambiar este valor según el efecto que desees.
    int fogColor = 0x222222; // Un gris medio. Por ejemplo, 0xAAAAAA o 0xC0C0C0.
    int fogR = (fogColor >> 16) & 0xFF;
    int fogG = (fogColor >> 8)  & 0xFF;
    int fogB = fogColor & 0xFF;

    // Mezcla lineal (interpolación) entre el color original y el de niebla
    int newR = (int)(r / (1.0 - fogFactor) + fogR * fogFactor);
    int newG = (int)(g / (1.0 - fogFactor) + fogG * fogFactor);
    int newB = (int)(b / (1.0 - fogFactor) + fogB * fogFactor);

    // Recomponer el color final
    return ((newR << 16) | (newG << 8) | newB);
}

int	apply_fog(int color, double distance, double max_distance)
{
	double	fogFactor;
	int		r, g, b;
	int		fogColor = 0x000000; // Color de la niebla (gris medio)
	int		fogR, fogG, fogB;
	int		newR, newG, newB;

	// Calcula el factor: 0.0 para distancia = 0, 1.0 para distance >= max_distance
	fogFactor = distance / max_distance;
	if (fogFactor > 1.0)
		fogFactor = 1.0;

	// Extraer componentes RGB del color original
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	// Extraer componentes del color de niebla
	fogR = (fogColor >> 16) & 0xFF;
	fogG = (fogColor >> 8) & 0xFF;
	fogB = fogColor & 0xFF;
	// Interpolación lineal entre el color original y el color de niebla
	newR = (int)(r * (1.0 - fogFactor) + fogR * fogFactor);
	newG = (int)(g * (1.0 - fogFactor) + fogG * fogFactor);
	newB = (int)(b * (1.0 - fogFactor) + fogB * fogFactor);
	// Recomponer el color
	return ((newR << 16) | (newG << 8) | newB);
}


void	put_pixel_fog(t_img *img, int x, int y, int color, double fogDistance, double max_distance)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		//*(unsigned int *)dst = color;
		*(unsigned int *)dst = apply_fog(color, fogDistance, max_distance);
	}
}


/**
 * Función que pone un píxel en una imagen en las coordenadas (x,
		y) con un color dado.
 * @param img Imagen a la que agregar el píxel.
 * @param x Coordenada X del píxel.
 * @param y Coordenada Y del píxel.
 * @param color Color en formato hexadecimal.
 */
void	put_pixel(t_img *img, t_ray_cast *rc, t_ray_cast_draw *rcw, int color)
{
	char	*dst;

	if (rc->x >= 0 && rc->x < WIDTH && rcw->y >= 0 && rcw->y < HEIGHT)
	{
		dst = img->addr + (rcw->y * img->line_length + rc->x * (img->bpp / 8));
		*(unsigned int *)dst = darken_color(color, rcw->d);
	}
}

void	put_pixel_clear(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * Función que limpia la imagen, poniéndola completamente negra (0x000000).
 * @param img Imagen a limpiar.
 */
void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_clear(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/**
 * Calcula la dirección del rayo para un píxel dado en la pantalla.
 * @param game Estructura de datos del juego,
	contiene la dirección del jugador y la orientación de la cámara.
 * @param x Coordenada X del píxel en la pantalla.
 * @param rayDirX Dirección del rayo en el eje X.
 * @param rayDirY Dirección del rayo en el eje Y.
 * @param cameraX Coordenada X en el espacio de la cámara.
 */
void	calculate_ray_direction(t_game *game, int x, double *rayDirX,
		double *rayDirY, double *cameraX)
{
	*cameraX = 2 * x / (double)WIDTH - 1;
	*rayDirX = game->dir_x + game->plane_x * (*cameraX);
	*rayDirY = game->dir_y + game->plane_y * (*cameraX);
}

/**
 * Inicializa la posición del rayo, calculando la distancia entre los rayos
 * y las celdas del mapa en el que se proyectan.
 * @param game Estructura de datos del juego.
 * @param rayDirX Dirección del rayo en el eje X.
 * @param rayDirY Dirección del rayo en el eje Y.
 * @param mapX Posición X del rayo en el mapa.
 * @param mapY Posición Y del rayo en el mapa.
 * @param deltaDistX Distancia entre el rayo y las celdas del mapa en el eje X.
 * @param deltaDistY Distancia entre el rayo y las celdas del mapa en el eje Y.
 */
void	initialize_ray_position(t_game *game, double rayDirX, double rayDirY,
		int *mapX, int *mapY, double *deltaDistX, double *deltaDistY)
{
	*mapX = (int)game->player_x;
	*mapY = (int)game->player_y;
	*deltaDistX = fabs(1 / rayDirX);
	*deltaDistY = fabs(1 / rayDirY);
}

/**
 * Realiza el algoritmo DDA (Digital Differential Analyzer), que determina
 * la intersección del rayo con una pared.
 * @param game Estructura de datos del juego.
 * @param mapX Coordenadas X del mapa.
 * @param mapY Coordenadas Y del mapa.
 * @param sideDistX Distancia a los bordes más cercanos del mapa en el eje X.
 * @param sideDistY Distancia a los bordes más cercanos del mapa en el eje Y.
 * @param deltaDistX Distancia entre el rayo y las celdas del mapa en el eje X.
 * @param deltaDistY Distancia entre el rayo y las celdas del mapa en el eje Y.
 * @param stepX Dirección de los pasos en el eje X.
 * @param stepY Dirección de los pasos en el eje Y.
 * @param side Lado de la pared que ha tocado el rayo.
 * @param hit Indicador de si el rayo ha colisionado con una pared.
 */
void	perform_dda(t_game *game, int *mapX, int *mapY, double *sideDistX,
		double *sideDistY, double deltaDistX, double deltaDistY, int *stepX,
		int *stepY, int *side, int *hit)
{
	while (!(*hit))
	{
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += deltaDistX;
			*mapX += *stepX;
			*side = 0;
		}
		else
		{
			*sideDistY += deltaDistY;
			*mapY += *stepY;
			*side = 1;
		}
		if (game->world_map[*mapY][*mapX] > 0)
			*hit = 1;
	}
}

/**
 * Calcula la distancia perpendicular a la pared tocada por el rayo.
 * Esto es crucial para la corrección de la proyección 3D.
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene información del rayo.
 * @return La distancia perpendicular entre el rayo y la pared tocada.
 */
double	calculate_perp_wall_dist(t_game *game, t_ray_cast *rc)
{
	double	perpWallDist;
	double	adjustment;

	if (rc->side == 0)
	{
		adjustment = 1;
		if (rc->rayDirX < 0)
			adjustment = -1;
		perpWallDist = (rc->mapX - game->player_x + (1 - adjustment) / 2)
			/ rc->rayDirX;
	}
	else
	{
		adjustment = 1;
		if (rc->rayDirY < 0)
			adjustment = -1;
		perpWallDist = (rc->mapY - game->player_y + (1 - adjustment) / 2)
			/ rc->rayDirY;
	}
	return (perpWallDist);
}

/**
 * Selecciona la textura que corresponde a la pared tocada por el rayo.
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene información del rayo.
 * @param texture Textura que se seleccionará según el rayo.
 */
void	select_texture(t_game *game, t_ray_cast *rc, t_img *texture)
{
	if (rc->side == 1)
	{
		if (rc->rayDirY < 0)
			*texture = game->textures[NORTH];
		else
			*texture = game->textures[SOUTH];
	}
	else
	{
		if (rc->rayDirX < 0)
			*texture = game->textures[WEST];
		else
			*texture = game->textures[EAST];
	}
}

/**
 * Calcula parámetros adicionales necesarios para dibujar la pared
 * en la pantalla (altura, posición, etc).
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene la información del rayo.
 * @param rcw Estructura donde se almacenarán los parámetros calculados.
 */
void	calculate_wall_params(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw)
{
	rcw->perpWallDist = calculate_perp_wall_dist(game, rc);
	rcw->lineHeight = (int)(HEIGHT / rcw->perpWallDist);
	rcw->drawStart = (HEIGHT - rcw->lineHeight) / 2;
	rcw->drawEnd = (HEIGHT + rcw->lineHeight) / 2;
	if (rcw->drawStart < 0)
		rcw->drawStart = 0;
	if (rcw->drawEnd >= HEIGHT)
		rcw->drawEnd = HEIGHT - 1;
	rcw->texNum = game->world_map[rc->mapY][rc->mapX] - 1;
}

/**

	* Calcula las coordenadas de la textura a utilizar para la pared tocada por el rayo.
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene la información del rayo.
 * @param rcw Estructura con los parámetros de dibujo de la pared.
 * @param texture Textura a utilizar para la pared.
 */
void	calculate_texture_coordinates(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw, t_img *texture)
{
	if (rc->side == 0)
		rcw->wallX = game->player_y + rcw->perpWallDist * rc->rayDirY;
	else
		rcw->wallX = game->player_x + rcw->perpWallDist * rc->rayDirX;
	rcw->wallX -= floor(rcw->wallX);
	rcw->texX = (int)(rcw->wallX * (double)(texture->width));
	if ((rc->side == 0 && rc->rayDirX > 0) || (rc->side == 1
			&& rc->rayDirY < 0))
		rcw->texX = texture->width - rcw->texX - 1;
}

/**
 * Dibuja la columna de pared en la pantalla, utilizando la textura seleccionada
 * para la pared.
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene la información del rayo.
 * @param rcw Estructura con los parámetros de dibujo de la pared.
 * @param texture Textura a usar para dibujar la pared.
 */
void	draw_wall_column(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw, t_img *texture)
{
	rcw->y = rcw->drawStart;
	while (rcw->y < rcw->drawEnd)
	{
		// Cálculo de la posición en la textura (igual que en tu código)
		rcw->d = rcw->y * 256 - HEIGHT * 128 + rcw->lineHeight * 128;
		rcw->texY = ((rcw->d * texture->height) / rcw->lineHeight) / 256;
		rcw->color = *(unsigned int *)(texture->addr + (rcw->texY
					* texture->line_length + rcw->texX * (texture->bpp / 8)));
		// Para la pared usamos la distancia perpendicular calculada
		put_pixel_fog(&game->img, rc->x, rcw->y, rcw->color, rcw->perpWallDist, 10.0);
		rcw->y++;
	}
}

/**
 * Dibuja el techo y el piso en la pantalla, fuera de la columna de la pared.
 * @param game Estructura de datos del juego.
 * @param rc Estructura que contiene la información del rayo.
 * @param rcw Estructura con los parámetros de dibujo de la pared.
 * @param vars Estructura con variables generales del juego.
 */
void	draw_ceiling_and_floor(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw, t_vars *vars)
{
	int x = rc->x;
	double currentDist;
	
	rcw->y = 0;
	while (rcw->y < rcw->drawStart)
	{
		// Evitar división por cero o valores extremos cerca del horizonte:
		currentDist = 1.0;
		if (HEIGHT - 2 * rcw->y != 0)
			currentDist = HEIGHT / (double)(HEIGHT - 2 * rcw->y);
		put_pixel_fog(&game->img, x, rcw->y, vars->colors->c_hex, currentDist, 10.0);
		rcw->y++;
	}
	rcw->y = rcw->drawEnd;
	while (rcw->y < HEIGHT)
	{
		currentDist = 1.0;
		if (2 * rcw->y - HEIGHT != 0)
			currentDist = HEIGHT / (double)(2 * rcw->y - HEIGHT);
		put_pixel_fog(&game->img, x, rcw->y, vars->colors->f_hex, currentDist, 10.0);
		rcw->y++;
	}
}


/**
 * Realiza el renderizado de una columna de pared, utilizando la textura
 * adecuada y dibujando el techo y el piso.
 * @param game Estructura de datos del juego.
 * @param vars Estructura con variables generales del juego.
 * @param rc Estructura que contiene la información del rayo.
 */
void	render_column(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	t_ray_cast_draw	rcw;
	t_img			texture;

	calculate_wall_params(game, rc, &rcw);
	select_texture(game, rc, &texture);
	calculate_texture_coordinates(game, rc, &rcw, &texture);
	draw_wall_column(game, rc, &rcw, &texture);
	draw_ceiling_and_floor(game, rc, &rcw, vars);
}

// Inicializa los valores de step y sideDist para cada dirección del rayo
void	initialize_step_and_sidedist(t_game *game, t_ray_cast *rc)
{
	// Si la dirección del rayo es negativa en el eje X,
	//	ajusta el paso y la distancia al lado.
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (game->player_x - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - game->player_x) * rc->deltaDistX;
	}
	// Lo mismo para el eje Y,
	//	ajustando el paso y la distancia al lado según la dirección del rayo.
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (game->player_y - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - game->player_y) * rc->deltaDistY;
	}
}

// Procesa el raycasting,
//	llama a la DDA para calcular la intersección y luego renderiza la columna
void	process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	// Realiza la DDA para obtener la intersección del rayo con una pared
	perform_dda(game, &rc->mapX, &rc->mapY, &rc->sideDistX, &rc->sideDistY,
			rc->deltaDistX, rc->deltaDistY, &rc->stepX, &rc->stepY, &rc->side,
			&rc->hit);
	// Renderiza la columna correspondiente a este rayo
	render_column(game, vars, rc);
}

// Renderiza la escena completa
void	render_scene(t_vars *vars, t_game *game)
{
	t_ray_cast	rc;

	rc.x = 0;
	// Recorre todos los rayos de la pantalla
	while (rc.x < WIDTH)
	{
		// Calcula la dirección del rayo para cada columna de la pantalla
		calculate_ray_direction(game, rc.x, &rc.rayDirX, &rc.rayDirY,
				&rc.cameraX);
		// Inicializa la posición y el paso del rayo
		initialize_ray_position(game, rc.rayDirX, rc.rayDirY, &rc.mapX,
				&rc.mapY, &rc.deltaDistX, &rc.deltaDistY);
		// Inicializa los pasos y distancias al lado para cada eje
		initialize_step_and_sidedist(game, &rc);
		rc.hit = 0;
		// Procesa el raycasting y renderiza la columna
		process_ray_casting(game, vars, &rc);
		rc.x++;
	}
}

// Funciones de movimiento del jugador

// Rota al jugador en un ángulo determinado
void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	// Calcula la nueva dirección del jugador
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	// Calcula el nuevo plano de visión del jugador
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

// Mueve al jugador hacia adelante
void	move_forward(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	// Calcula la nueva posición del jugador al moverse hacia adelante
	newX = game->player_x + game->dir_x * MOVE_SPEED;
	newY = game->player_y + game->dir_y * MOVE_SPEED;
	// Ajustes para evitar que el jugador atraviese paredes por pequeños márgenes
	offsetX = 0.2;
	offsetY = 0.2;
	if (game->dir_x < 0)
		offsetX = -0.2;
	if (game->dir_y < 0)
		offsetY = -0.2;
	// Si la nueva posición no colisiona con una pared, mueve al jugador
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0)
		game->player_y = newY;
}

// Mueve al jugador hacia atrás
void	move_backward(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	// Calcula la nueva posición del jugador al moverse hacia atrás
	newX = game->player_x - game->dir_x * MOVE_SPEED;
	newY = game->player_y - game->dir_y * MOVE_SPEED;
	// Ajustes similares a los de moverse hacia adelante
	offsetX = -0.2;
	offsetY = -0.2;
	if (game->dir_x < 0)
		offsetX = 0.2;
	if (game->dir_y < 0)
		offsetY = 0.2;
	// Verifica la colisión antes de mover al jugador
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0)
		game->player_y = newY;
}

// Mueve al jugador hacia la derecha
void	move_right(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	// Calcula la nueva posición del jugador al moverse hacia la derecha
	newX = game->player_x + game->plane_x * MOVE_SPEED;
	newY = game->player_y + game->plane_y * MOVE_SPEED;
	// Ajustes para evitar atravesar paredes
	offsetX = 0.2;
	offsetY = 0.2;
	if (game->plane_x < 0)
		offsetX = -0.2;
	if (game->plane_y < 0)
		offsetY = -0.2;
	// Verifica la colisión antes de mover al jugador
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0)
		game->player_y = newY;
}

// Mueve al jugador hacia la izquierda
void	move_left(t_game *game)
{
	double	newX;
	double	newY;
	double	offsetX;
	double	offsetY;

	// Calcula la nueva posición del jugador al moverse hacia la izquierda
	newX = game->player_x - game->plane_x * MOVE_SPEED;
	newY = game->player_y - game->plane_y * MOVE_SPEED;
	// Ajustes similares a los otros movimientos
	offsetX = -0.2;
	offsetY = -0.2;
	if (game->plane_x < 0)
		offsetX = 0.2;
	if (game->plane_y < 0)
		offsetY = 0.2;
	// Verifica la colisión antes de mover al jugador
	if (game->world_map[(int)(game->player_y)][(int)(newX + offsetX)] == 0)
		game->player_x = newX;
	if (game->world_map[(int)(newY + offsetY)][(int)(game->player_x)] == 0)
		game->player_y = newY;
}

// Funciones para controlar las teclas

// Cierra la ventana y limpia
int	close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}

// Actualiza el movimiento del jugador según las teclas presionadas
void	update_movement(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_d)
		move_right(game);
	if (game->key_a)
		move_left(game);
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
}

// Función que se llama cuando se presiona una tecla
int	key_press(int key, t_vars *vars)
{
	if (key == 65307)
		close_window(vars); // Cierra la ventana con la tecla ESC
	if (key == 119)         // 'W' para mover hacia adelante
		vars->game->key_w = 1;
	if (key == 115) // 'S' para mover hacia atrás
		vars->game->key_s = 1;
	if (key == 97) // 'A' para mover hacia la izquierda
		vars->game->key_a = 1;
	if (key == 100) // 'D' para mover hacia la derecha
		vars->game->key_d = 1;
	if (key == 65361) // Flecha izquierda para rotar a la izquierda
		vars->game->key_left = 1;
	if (key == 65363) // Flecha derecha para rotar a la derecha
		vars->game->key_right = 1;
	return (0);
}

// Función que se llama cuando se suelta una tecla
int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->key_w = 0;
	if (key == 115)
		game->key_s = 0;
	if (key == 97)
		game->key_a = 0;
	if (key == 100)
		game->key_d = 0;
	if (key == 65361)
		game->key_left = 0;
	if (key == 65363)
		game->key_right = 0;
	return (0);
}

void    draw_square(t_game *game, int x, int y, int color)
{
    int i, j;
    int start_x = MAP_OFFSET + x * TILE_SIZE;
    int start_y = MAP_OFFSET + y * TILE_SIZE;

    for (i = 0; i < TILE_SIZE; i++)
    {
        for (j = 0; j < TILE_SIZE; j++)
        {
            mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i, color);
        }
    }
}

void    draw_player(t_game *game, int x, int y, int color)
{
    int i, j;
    int start_x = MAP_OFFSET + x * TILE_SIZE;
    int start_y = MAP_OFFSET + y * TILE_SIZE;

    for (i = 0; i < (TILE_SIZE / 5); i++)
    {
        for (j = 0; j < (TILE_SIZE / 5); j++)
        {
            mlx_pixel_put(game->mlx, game->win, x + j, y + i, color);
        }
    }
}

void draw_minimap(t_game *game)
{
    int start_x = (int)(game->player_x) - MINIMAP_RADIUS; // Limite inferior de X
    int start_y = (int)(game->player_y) - MINIMAP_RADIUS; // Limite inferior de Y
    int end_x = (int)(game->player_x) + MINIMAP_RADIUS;   // Limite superior de X
    int end_y = (int)(game->player_y) + MINIMAP_RADIUS;   // Limite superior de Y

    // Asegurarse de no salir de los límites del mapa
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x >= game->map_width) end_x = game->map_width - 1;
    if (end_y >= game->map_height) end_y = game->map_height - 1;

    // Dibujar las celdas del minimapa dentro del área visible
    for (int y = start_y; y <= end_y; y++)
    {
        for (int x = start_x; x <= end_x; x++)
        {
            if (game->world_map[y][x] == 1)
                draw_square(game, x - start_x, y - start_y, 0xFFFFFF); // Blanco para paredes
            else
                draw_square(game, x - start_x, y - start_y, 0x000000); // Negro para espacios vacíos
        }
    }    
    // Dibujar el jugador como un cuadrado de tamaño TILE_SIZE
    draw_square(game, game->player_x - start_x, game->player_y - start_y, 0xFF0000);  // Rojo para el jugador
}

int	render(t_vars *vars)
{
	clear_image(&vars->game->img);
	// Limpia la imagen
	update_movement(vars->game);
	// Actualiza el movimiento del jugador
	render_scene(vars,
					vars->game);
	// Renderiza la escena
	mlx_put_image_to_window(vars->game->mlx, vars->game->win,
			vars->game->img.img, 0, 0); // Muestra la imagen
	draw_minimap(vars->game);
	return (0);
}

