#include "../include/cub3d.h"

// Función para dibujar un píxel en la imagen
void put_pixel(t_img *img, int x, int y, int color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        char *dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

// Limpia la imagen llenándola de negro
void clear_image(t_img *img)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
        for (x = 0; x < WIDTH; x++)
            put_pixel(img, x, y, 0x000000);
}

// Función que realiza el raycasting y dibuja la escena
void render_scene(t_game *game)
{
    for (int x = 0; x < WIDTH; x++)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = game->dir_x + game->plane_x * cameraX;
        double rayDirY = game->dir_y + game->plane_y * cameraX;
        
        int mapX = (int)game->player_x;
        int mapY = (int)game->player_y;
        
        double sideDistX;
        double sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist = 0;
        
        int stepX, stepY;
        int hit = 0;
        int side = 0;  // 0: impacto en eje X, 1: en eje Y

        /* Si el jugador está dentro de una pared, evitamos el bucle DDA */
        if (game->world_map[mapY][mapX] > 0)
        {
            hit = 1;
            perpWallDist = 1.0;
        }
        else
        {
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (game->player_x - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - game->player_x) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (game->player_y - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - game->player_y) * deltaDistY;
            }
            
            int iterations = 0;
            int max_iterations = game->map_width * game->map_height;
            while (!hit && iterations < max_iterations)
            {
                iterations++;
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
                
                /* Si se sale del mapa, forzamos la salida */
                if (mapX < 0 || mapX >= game->map_width ||
                    mapY < 0 || mapY >= game->map_height)
                {
                    hit = 1;
                    break;
                }
                
                /* Si se llega a una pared, salimos */
                if (game->world_map[mapY][mapX] > 0)
                {
                    hit = 1;
                    break;
                }
                
                /* Si la diferencia entre distancias laterales es casi cero,
                   forzamos la salida para evitar bucles infinitos */
                if (fabs(sideDistX - sideDistY) < 1e-9)
                {
                    hit = 1;
                    break;
                }
            }
            
            /* Si se excede el número máximo de iteraciones, asignamos un valor por defecto */
            if (iterations >= max_iterations)
                perpWallDist = 1.0;
            else
            {
                if (side == 0)
                    perpWallDist = (mapX - game->player_x + (1 - stepX) / 2.0) / rayDirX;
                else
                    perpWallDist = (mapY - game->player_y + (1 - stepY) / 2.0) / rayDirY;
                /* Para evitar divisiones por cero o distancias extremadamente cortas */
                if (perpWallDist < 0.0001)
                    perpWallDist = 0.0001;
            }
        }
        
        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        int wallColor = 0xFF0000;
        if (side == 1)
            wallColor = wallColor / 2;
        
        /* Dibuja el techo */
        for (int y = 0; y < drawStart; y++)
            put_pixel(&game->img, x, y, 0x00BFFF);
        /* Dibuja la pared */
        for (int y = drawStart; y < drawEnd; y++)
            put_pixel(&game->img, x, y, wallColor);
        /* Dibuja el suelo */
        for (int y = drawEnd; y < HEIGHT; y++)
            put_pixel(&game->img, x, y, 0x8B4513);
    }
}



void rotate_player(t_game *game, double angle)
{
    double old_dir_x = game->dir_x;
    game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
    game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);

    double old_plane_x = game->plane_x;
    game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
    game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

void update_movement(t_game *game)
{
    double margin = 0.2;  // Margen de colisión
    double newX, newY;

    /* Movimiento hacia adelante (W) */
    if (game->key_w)
    {
        newX = game->player_x + game->dir_x * MOVE_SPEED;
        newY = game->player_y + game->dir_y * MOVE_SPEED;
        /* Se comprueba la colisión en el eje X: se agrega el margen en la dirección del movimiento */
        if (game->world_map[(int)(game->player_y)]
                          [(int)(newX + (game->dir_x > 0 ? margin : -margin))] == 0)
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
                          [(int)(newX - (game->dir_x > 0 ? margin : -margin))] == 0)
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
                          [(int)(newX + (game->plane_x > 0 ? margin : -margin))] == 0)
            game->player_x = newX;
        if (game->world_map[(int)(newY + (game->plane_y > 0 ? margin : -margin))]
                          [(int)(game->player_x)] == 0)
            game->player_y = newY;
    }
    
    /* Movimiento lateral hacia la izquierda (A) */
    if (game->key_a)
    {
        newX = game->player_x - game->plane_x * MOVE_SPEED;
        newY = game->player_y - game->plane_y * MOVE_SPEED;
        if (game->world_map[(int)(game->player_y)]
                          [(int)(newX - (game->plane_x > 0 ? margin : -margin))] == 0)
            game->player_x = newX;
        if (game->world_map[(int)(newY - (game->plane_y > 0 ? margin : -margin))]
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
int key_press(int key, t_game *game)
{
    if (key == 65307) // ESC
        exit(0);
    if (key == 119) game->key_w = 1;
    if (key == 115) game->key_s = 1;
    if (key == 97)  game->key_a = 1;
    if (key == 100) game->key_d = 1;
    if (key == 65361) game->key_left = 1;
    if (key == 65363) game->key_right = 1;
    return 0;
}

// Callback para soltar una tecla
int key_release(int key, t_game *game)
{
    if (key == 119) game->key_w = 0;
    if (key == 115) game->key_s = 0;
    if (key == 97)  game->key_a = 0;
    if (key == 100) game->key_d = 0;
    if (key == 65361) game->key_left = 0;
    if (key == 65363) game->key_right = 0;
    return 0;
}

// Callback para cerrar la ventana (al hacer clic en la X)
int close_window(t_game *game)
{
    exit(0);
    return 0;
}

// Función de renderizado (se llama en cada iteración del loop)
int render(t_game *game)
{
    clear_image(&game->img);
    update_movement(game);
    render_scene(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return 0;
}
