#include "../include/cub3d.h"

static void free_matrix(char **mtx)
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
	free_matrix(vars->file);
	free_paths(vars);
	free_colors(vars);
	free(vars->player);
	free(vars);
	printf("\nEND\n\n");
}