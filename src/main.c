/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:23:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/05 11:02:03 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// valgrind --leak-check=full --track-fds=yes --track-origins=yes ./cub3d maps/map.cub

// checkear que posiciones x-y estan bien

// mira el mapa parseado en terminal y compara con el archivo, esto te vale
// o lo necesitas todo cuadrado? incluso los espacios que faltan? el starting
// pos ya te lo paso como 0 en el mapa parseado

// floodfill para asegurar mapa valido

// checkear caracteres repetidos en mapa != '1' || '0'

// Colores FLOOR y CEILING
// crear y hacer split y atoi a colors->f y colors->c
// para hacer colors->f_r colors->f_g colors->f_b (RGB)(INT)

// integrar el raycasting en base a esto

// hacer un makefile bonito

// y no mucho mas??? va a ser corto esto :)

// esta funcion es solo para que veas donde estan las cosas hasta ahora
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
	for (int i = 0; i < vars->game->map_height ; i++)
	{
		for (int j = 0; j < vars->game->map_width; j++)
		{
			printf("%d", vars->game->world_map[i][j]);
		}
        printf("\n");
	}
}

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	init_vars(&vars);
	if (check_args(argc, argv, vars) == OK && check_map_valid(vars) == OK)
		print_status(vars);
	mlx_hook(vars->game->win, 2, 1L << 0, key_press, vars->game);
	mlx_hook(vars->game->win, 3, 1L << 1, key_release, vars->game);
	mlx_hook(vars->game->win, 17, 0, close_window, vars->game);
	mlx_loop_hook(vars->game->mlx, render, vars->game);
	mlx_loop(vars->game->mlx);
	clean_exit(vars);
	return (0);
}
