#include "../include/cub3d.h"

// Función para dibujar un píxel en la imagen
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// Limpia la imagen llenándola de negro
void	clear_image(t_img *img)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++)
			put_pixel(img, x, y, 0x000000);
}

// Función que realiza el raycasting y dibuja la escena
void	render_scene(t_game *game)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
		double perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;
	int		d;
	int		texY;
	int		color;

	for (int x = 0; x < WIDTH; x++)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = game->dir_x + game->plane_x * cameraX;
		rayDirY = game->dir_y + game->plane_y * cameraX;
		mapX = (int)game->player_x;
		mapY = (int)game->player_y;
		double sideDistX, sideDistY;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		int stepX, stepY, hit = 0, side;
		stepX = (rayDirX < 0) ? -1 : 1;
		sideDistX = (rayDirX < 0) ? (game->player_x - mapX) * deltaDistX
									: (mapX + 1.0 - game->player_x)
										* deltaDistX;
		stepY = (rayDirY < 0) ? -1 : 1;
		sideDistY = (rayDirY < 0) ? (game->player_y - mapY) * deltaDistY
									: (mapY + 1.0 - game->player_y)
										* deltaDistY;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->world_map[mapY][mapX] > 0)
				hit = 1;
		}
		perpWallDist = (side == 0) ? (mapX - game->player_x + (1 - stepX) / 2)
			/ rayDirX
									: (mapY - game->player_y + (1 - stepY) / 2)
										/ rayDirY;
		lineHeight = (int)(HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		texNum = game->world_map[mapY][mapX] - 1;
		t_img texture = game->textures[side ? (rayDirY < 0 ? NORTH : SOUTH)
											: (rayDirX < 0 ? WEST : EAST)];
		double wallX = (side == 0) ? game->player_y + perpWallDist * rayDirY
									: game->player_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		texX = (int)(wallX * (double)(texture.width));
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = texture.width - texX - 1;
		for (int y = drawStart; y < drawEnd; y++)
		{
			d = y * 256 - HEIGHT * 128 + lineHeight * 128;
			texY = ((d * texture.height) / lineHeight) / 256;
			color = *(unsigned int *)(texture.addr + (texY * texture.line_length
						+ texX * (texture.bpp / 8)));
			put_pixel(&game->img, x, y, color);
		}
		for (int y = 0; y < drawStart; y++)
			put_pixel(&game->img, x, y, 0x00BFFF);
		for (int y = drawEnd; y < HEIGHT; y++)
			put_pixel(&game->img, x, y, 0x8B4513);
	}
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void	update_movement(t_game *game)
{
	double margin = 0.2; // Margen de colisión
	double newX, newY;
	/* Movimiento hacia adelante (W) */
	if (game->key_w)
	{
		newX = game->player_x + game->dir_x * MOVE_SPEED;
		newY = game->player_y + game->dir_y * MOVE_SPEED;
		/* Se comprueba la colisión en el eje X: se agrega el margen en la dirección del movimiento */
		if (game->world_map[(int)(game->player_y)]
							[(int)(newX + (game->dir_x > 0 ? margin :
										-margin))] == 0)
			game->player_x = newX;
		/* Se comprueba la colisión en el eje Y */
		if (game->world_map[(int)(newY + (game->dir_y > 0 ? margin : -margin))]
							[(int)(game->player_x)] == 0)
			game->player_y = newY;
	}
	/* Movimiento hacia atrás (S) */
	if (game->key_s)
	{
		newX = game->player_x - game->dir_x * MOVE_SPEED;
		newY = game->player_y - game->dir_y * MOVE_SPEED;
		if (game->world_map[(int)(game->player_y)]
							[(int)(newX - (game->dir_x > 0 ? margin :
										-margin))] == 0)
			game->player_x = newX;
		if (game->world_map[(int)(newY - (game->dir_y > 0 ? margin : -margin))]
							[(int)(game->player_x)] == 0)
			game->player_y = newY;
	}
	/* Movimiento lateral hacia la derecha (D) */
	if (game->key_d)
	{
		newX = game->player_x + game->plane_x * MOVE_SPEED;
		newY = game->player_y + game->plane_y * MOVE_SPEED;
		if (game->world_map[(int)(game->player_y)]
							[(int)(newX + (game->plane_x > 0 ? margin :
										-margin))] == 0)
			game->player_x = newX;
		if (game->world_map[(int)(newY + (game->plane_y > 0 ? margin :
					-margin))]
							[(int)(game->player_x)] == 0)
			game->player_y = newY;
	}
	/* Movimiento lateral hacia la izquierda (A) */
	if (game->key_a)
	{
		newX = game->player_x - game->plane_x * MOVE_SPEED;
		newY = game->player_y - game->plane_y * MOVE_SPEED;
		if (game->world_map[(int)(game->player_y)]
							[(int)(newX - (game->plane_x > 0 ? margin :
										-margin))] == 0)
			game->player_x = newX;
		if (game->world_map[(int)(newY - (game->plane_y > 0 ? margin :
					-margin))]
							[(int)(game->player_x)] == 0)
			game->player_y = newY;
	}
	/* Rotación */
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
}

// Callback para presionar una tecla
int	key_press(int key, t_vars *vars)
{
	if (key == 65307) // ESC
		close_window(vars);
	if (key == 119)
		vars->game->key_w = 1;
	if (key == 115)
		vars->game->key_s = 1;
	if (key == 97)
		vars->game->key_a = 1;
	if (key == 100)
		vars->game->key_d = 1;
	if (key == 65361)
		vars->game->key_left = 1;
	if (key == 65363)
		vars->game->key_right = 1;
	return (0);
}

// Callback para soltar una tecla
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

// Callback para cerrar la ventana (al hacer clic en la X)
int	close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}

// Función de renderizado (se llama en cada iteración del loop)
int	render(t_game *game)
{
	clear_image(&game->img);
	update_movement(game);
	render_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
