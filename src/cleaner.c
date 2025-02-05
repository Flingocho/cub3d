#include "../include/cub3d.h"

static void free_char_matrix(char **mtx)
{
	int i;

	i = 0;
	while(mtx[i])
		free(mtx[i++]);
	free(mtx);
}

static void free_int_matrix(int **mtx)
{
	int i;

	i = 0;
	while(mtx[i])
		free(mtx[i++]);
	free(mtx);
}

static void free_paths(t_vars *vars)
{
	free(vars->paths->no);
	free(vars->paths->so);
	free(vars->paths->we);
	free(vars->paths->ea);
	free(vars->paths);
}

static void free_colors(t_vars *vars)
{
	free(vars->colors->c);
	free(vars->colors->f);
	free(vars->colors);
}

void clean_exit(t_vars *vars)
{
	printf("\nStarting cleaner\n");
	mlx_loop_end(vars->game->mlx);
	mlx_destroy_image(vars->game->mlx, vars->game->img.img);
	mlx_destroy_window(vars->game->mlx, vars->game->win);
	mlx_destroy_display(vars->game->mlx);
	free(vars->game->mlx);
	free(vars->game->win);
	free(vars->game->img.img);
	free_char_matrix(vars->file);
	free_int_matrix(vars->game->world_map);
	free_paths(vars);
	free_colors(vars);
	free(vars->paths);
	free(vars->player);
	free(vars->colors);
	free(vars->game);
	free(vars);
	printf("\nEND\n\n");
}