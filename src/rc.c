#include "../include/cub3d.h"

/*
** Función auxiliar para eliminar espacios iniciales de una cadena.
*/
static char *trim_leading_spaces(char *s)
{
    while (s && *s && isspace((unsigned char)*s))
        s++;
    return s;
}

/*
** Función para contar la cantidad de líneas en un buffer (separadas por '\n').
*/
static int count_lines(char *buffer)
{
    int count = 0;
    char *p = buffer;
    while (*p)
    {
        if (*p == '\n')
            count++;
        p++;
    }
    return count;
}

/*
** Función para dividir el buffer en líneas. Devuelve un arreglo de punteros a
** cada línea (el arreglo y las líneas usan la memoria del buffer original).
*/
static char **split_lines(char *buffer, int total_lines)
{
    char **lines = malloc(sizeof(char *) * (total_lines + 1));
    if (!lines)
        return (NULL);
    int i = 0;
    lines[i++] = buffer;
    for (char *p = buffer; *p; p++)
    {
        if (*p == '\n')
        {
            *p = '\0';
            if (*(p + 1) != '\0')
                lines[i++] = p + 1;
        }
    }
    lines[i] = NULL;
    return lines;
}

/*
** Función para parsear el archivo .cub.
**
** Se asume que la primera línea cuyo contenido (después de eliminar espacios)
** comience con '1' es el inicio del mapa, y que todas las líneas siguientes forman
** el mapa.
**
** Se determina el alto (número de líneas) y el ancho (longitud máxima) del mapa,
** y se reserva una matriz dinámica en game->world_map.
**
** Además, si se encuentra algún caracter entre 'N', 'S', 'E' o 'W', se establece
** la posición y orientación inicial del jugador, reemplazándolo por '0' en el mapa.
*/
int parse_map_file(const char *filename, t_game *game)
{
    int fd;
    char *buffer;
    int bytes_read;
    int total_lines, map_start = -1;
    char **lines;
    int i, j;

    buffer = malloc(BUFF_SIZE + 1);
    if (!buffer)
        return (fprintf(stderr, "Error de malloc\n"), 0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        free(buffer);
        return 0;
    }
    bytes_read = read(fd, buffer, BUFF_SIZE);
    if (bytes_read <= 0)
    {
        perror("Error al leer el archivo");
        free(buffer);
        close(fd);
        return 0;
    }
    buffer[bytes_read] = '\0';
    close(fd);

    total_lines = count_lines(buffer) + 1;
    lines = split_lines(buffer, total_lines);
    if (!lines)
    {
        free(buffer);
        return (fprintf(stderr, "Error al dividir líneas\n"), 0);
    }

    /* Busca la primera línea cuyo contenido (después de eliminar espacios)
       comience con '1'. Esa será la primera línea del mapa. */
    for (i = 0; lines[i] != NULL; i++)
    {
        char *trim = trim_leading_spaces(lines[i]);
        if (*trim == '1')
        {
            map_start = i;
            break;
        }
    }
    if (map_start == -1)
    {
        fprintf(stderr, "No se encontró inicio del mapa en el archivo.\n");
        free(lines);
        free(buffer);
        return 0;
    }

    /* Determina el alto del mapa (todas las líneas desde map_start hasta el final) */
    game->map_height = 0;
    for (i = map_start; lines[i] != NULL; i++)
        game->map_height++;
    /* Determina el ancho máximo */
    game->map_width = 0;
    for (i = map_start; lines[i] != NULL; i++)
    {
        int len = strlen(lines[i]);
        if (len > game->map_width)
            game->map_width = len;
    }
    /* Reserva la matriz del mapa */
    game->world_map = malloc(sizeof(int *) * game->map_height);
    if (!game->world_map)
    {
        fprintf(stderr, "Error de malloc en world_map.\n");
        free(lines);
        free(buffer);
        return 0;
    }
    for (i = 0; i < game->map_height; i++)
    {
        game->world_map[i] = malloc(sizeof(int) * game->map_width);
        if (!game->world_map[i])
        {
            fprintf(stderr, "Error de malloc en world_map[%d].\n", i);
            while (--i >= 0)
                free(game->world_map[i]);
            free(game->world_map);
            free(lines);
            free(buffer);
            return 0;
        }
    }

    /* Procesa cada línea del mapa */
    for (i = 0; i < game->map_height; i++)
    {
        char *line = lines[map_start + i];
        int len = strlen(line);
        for (j = 0; j < game->map_width; j++)
        {
            char c = (j < len) ? line[j] : ' '; // Rellena con espacios si la línea es corta
            if (c == ' ')
            {
                game->world_map[i][j] = 1; // Considera espacio como pared
            }
            else if (c == '1')
            {
                game->world_map[i][j] = 1;
            }
            else if (c == '0')
            {
                game->world_map[i][j] = 0;
            }
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->world_map[i][j] = 0; // Se reemplaza por espacio vacío
                /* Configura la posición del jugador en el centro de la celda */
                game->player_x = j + 0.5;
                game->player_y = i + 0.5;
                /* Configura la dirección y el plano de cámara según la orientación */
                if (c == 'N')
                {
                    game->dir_x = 0;
                    game->dir_y = -1;
                    game->plane_x = 0.66;
                    game->plane_y = 0;
                }
                else if (c == 'S')
                {
                    game->dir_x = 0;
                    game->dir_y = 1;
                    game->plane_x = -0.66;
                    game->plane_y = 0;
                }
                else if (c == 'E')
                {
                    game->dir_x = 1;
                    game->dir_y = 0;
                    game->plane_x = 0;
                    game->plane_y = 0.66;
                }
                else if (c == 'W')
                {
                    game->dir_x = -1;
                    game->dir_y = 0;
                    game->plane_x = 0;
                    game->plane_y = -0.66;
                }
            }
            else
            {
                fprintf(stderr, "Carácter inválido en el mapa: '%c'\n", c);
                /* Liberar memoria antes de retornar error */
                for (int k = 0; k <= i; k++)
                    free(game->world_map[k]);
                free(game->world_map);
                free(lines);
                free(buffer);
                return 0;
            }
        }
    }
    free(lines);
    free(buffer);
    return 1;
}

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
