/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:23:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/05 09:38:57 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// valgrind --leak-check=full --track-fds=yes --track-origins=yes ./cub3d maps/map.cub

//checkear que posiciones x-y estan bien

//mira el mapa parseado en terminal y compara con el archivo, esto te vale
//o lo necesitas todo cuadrado? incluso los espacios que faltan? el starting
//pos ya te lo paso como 0 en el mapa parseado

//floodfill para asegurar mapa valido

//checkear caracteres repetidos en mapa != '1' || '0'

//Colores FLOOR y CEILING
//crear y hacer split y atoi a colors->f y colors->c
//para hacer colors->f_r colors->f_g colors->f_b (RGB)(INT)

//integrar el raycasting en base a esto

//hacer un makefile bonito

//y no mucho mas??? va a ser corto esto :)

//esta funcion es solo para que veas donde estan las cosas hasta ahora
void	print_status(t_vars *vars)
{
	printf("\nPATHS:\n");
	printf("NO: %s\n", vars->paths->no);
	printf("SO: %s\n", vars->paths->so);
	printf("WE: %s\n", vars->paths->we);
	printf("EA: %s\n", vars->paths->ea);
	printf("\nCOLORS:\n");
	printf("Floor: %s\n", vars->colors->f);
	printf("Ceiling: %s\n", vars->colors->c);
	printf("\nPlAYER\n");
	printf("Starting orientation: %c\n", vars->player->start_orientation);
	printf("Starting X pos: %d\n", vars->player->x_start);
	printf("Starting Y pos: %d\n", vars->player->y_start);
	printf("\nParsed Map:\n");
	for (int i = 0; vars->map[i]; i++)
		printf("%s\n", vars->map[i]);
}

int main(int argc, char *argv[])
{
    t_game game;

    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <archivo.cub>\n", argv[0]);
        return (1);
    }

    /* Inicializa los flags de teclas en 0 */
    game.key_w = 0;
    game.key_a = 0;
    game.key_s = 0;
    game.key_d = 0;
    game.key_left = 0;
    game.key_right = 0;

    /* Intenta parsear el archivo .cub. Si falla, se aborta. */
    if (!parse_map_file(argv[1], &game))
    {
        fprintf(stderr, "Error al parsear el archivo %s\n", argv[1]);
        return (1);
    }

    /*
    ** Si el archivo .cub no definió la posición/orientación del jugador (por ejemplo,
    ** porque no se encontró un caracter 'N','S','E' o 'W'), se aborta.
    */
    if (game.dir_x == 0 && game.dir_y == 0)
    {
        fprintf(stderr, "El archivo .cub debe definir la posición y orientación del jugador.\n");
        return (1);
    }

    /* Inicializa MLX y crea la ventana e imagen */
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Raycasting");
    game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bpp,
                                        &game.img.line_length, &game.img.endian);

    /* Hooks de MLX */
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop_hook(game.mlx, render, &game);

    mlx_loop(game.mlx);

    return 0;
}
