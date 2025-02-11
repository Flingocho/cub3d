/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidal-t <jvidal-t@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:23:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/11 18:04:50 by jvidal-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_images(void *mlx, void *win)
{
	void	*img1;
	void	*img2;
	int		i;

	img1 = mlx_xpm_file_to_image(mlx, "textures/title01.xpm", &(int){WIDTH},
			&(int){HEIGHT});
	if (!img1)
		return ;
	img2 = mlx_xpm_file_to_image(mlx, "textures/title02.xpm", &(int){WIDTH},
			&(int){HEIGHT});
	if (!img2)
		return ((void)mlx_destroy_image(mlx, img1));
	i = 0;
	while (i < 25)
	{
		if (i % 2 == 0)
			mlx_put_image_to_window(mlx, win, img1, 0, 0);
		else
			mlx_put_image_to_window(mlx, win, img2, 0, 0);
		usleep(100000);
		i++;
	}
	mlx_destroy_image(mlx, img1);
	mlx_destroy_image(mlx, img2);
}

int	main(int argc, char *argv[])
{
	t_vars	*vars;
	int		x;
	int		y;

	init_vars(&vars);
	if (!(check_args(argc, argv, vars) == OK && check_map_valid(vars) == OK))
		exit(1);
	load_textures(vars);
	draw_images(vars->game->mlx, vars->game->win);
	mlx_hook(vars->game->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->game->win, 3, 1L << 1, key_release, vars->game);
	mlx_hook(vars->game->win, 17, 0, close_window, vars);
	mlx_loop_hook(vars->game->mlx, render, vars);
	mlx_loop(vars->game->mlx);
	clean_exit(vars);
	return (0);
}
//void	print_status(t_vars *vars)
// {
// 	printf("\nPATHS:\n");
// 	printf("NO: %s\n", vars->paths->no);
// 	printf("SO: %s\n", vars->paths->so);
// 	printf("WE: %s\n", vars->paths->we);
// 	printf("EA: %s\n", vars->paths->ea);
// 	printf("\nCOLORS:\n");
// 	printf("Floor: %s\n", vars->colors->f);
// 	printf("Ceiling: %s\n", vars->colors->c);
// 	printf("\nPlAYER\n");
// 	printf("Starting orientation: %c\n", vars->player->start_orientation);
// 	printf("Starting X pos: %d\n", vars->player->x_start);
// 	printf("Starting Y pos: %d\n", vars->player->y_start);
// 	printf("\nParsed Map:\n");
// 	for (int i = 0; i < vars->game->map_height; i++)
// 	{
// 		for (int j = 0; j < vars->game->map_width; j++)
// 		{
// 			printf("%d", vars->game->world_map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }
