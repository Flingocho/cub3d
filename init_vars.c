#include "cub3d.h"

void	init_vars(t_vars **vars)
{
    //PROTEGEME MAMAÑEMA
	*vars = ft_calloc(1, sizeof(t_vars));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
    (*vars)->player = ft_calloc(1, sizeof(t_player));
}
