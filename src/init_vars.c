#include "../include/cub3d.h"

void	init_vars(t_vars **vars)
{
    //PROTEGEME MAMAÑEMA
	*vars = ft_calloc(1, sizeof(t_vars));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
    (*vars)->player = ft_calloc(1, sizeof(t_player));
	(*vars)->game = ft_calloc(1, sizeof(t_game));
	(*vars)->game->mlx = mlx_init();
    (*vars)->game->win = mlx_new_window((*vars)->game->mlx, WIDTH, HEIGHT, "Cub3d");
    (*vars)->game->img.img = mlx_new_image((*vars)->game->mlx, WIDTH, HEIGHT);
    (*vars)->game->img.addr = mlx_get_data_addr((*vars)->game->img.img, &(*vars)->game->img.bpp,
                                        &(*vars)->game->img.line_length, &(*vars)->game->img.endian);
}
