#include "../include/cub3d.h"

void load_textures(t_game *game)
{
    char *texture_paths[4] = {
        "textures/wall_north.xpm",
        "textures/wall_south.xpm",
        "textures/wall_east.xpm",
        "textures/wall_west.xpm"
    };

    for (int i = 0; i < 4; i++)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
            texture_paths[i], &game->textures[i].width, &game->textures[i].height);
        if (!game->textures[i].img)
        {
            printf("Error: No se pudo cargar la textura %s\n", texture_paths[i]);
            exit(1);
        }
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].line_length, &game->textures[i].endian);
    }
}


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
    load_textures((*vars)->game);
}
