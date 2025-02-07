#include "../include/cub3d.h"

void free_char_matrix(char **mtx)
{
	int i;

	i = 0;
	while(mtx[i])
		free(mtx[i++]);
	free(mtx);
}

static void free_int_matrix(t_vars *vars, int **mtx)
{
	int i;

	i = 0;
	while(i < vars->game->map_height)
		free(mtx[i++]);
	free(mtx);
}

static void free_paths(t_vars *vars)
{
	free(vars->paths->no);
	free(vars->paths->so);
	free(vars->paths->we);
	free(vars->paths->ea);
}

static void free_colors(t_vars *vars)
{
	free(vars->colors->c);
	free(vars->colors->f);
}

static void free_textures(t_game *game)
{
    int i = 0;
    while (i < 4)
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
        i++;
    }
	while(BONUS && i < 8)
	{
		if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
        i++;
	}
}



void clean_exit(t_vars *vars)
{
	printf("\nStarting cleaner\n");
	mlx_loop_end(vars->game->mlx);
	mlx_destroy_image(vars->game->mlx, vars->game->img.img);
	free_textures(vars->game);
	mlx_destroy_window(vars->game->mlx, vars->game->win);
	mlx_destroy_display(vars->game->mlx);
	free(vars->game->mlx);
	free_char_matrix(vars->file);
	free_int_matrix(vars, vars->game->world_map);
	free_paths(vars);
	free_colors(vars);
	free(vars->paths);
	free(vars->player);
	free(vars->colors);
	free(vars->game);
	free(vars);
	printf("\nEND\n\n");
}
