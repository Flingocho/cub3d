/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:36:12 by mrubal-c          #+#    #+#             */
/*   Updated: 2025/02/07 13:39:53 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	put_pixel_clear(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	clear_image(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_clear(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

static void	render_scene(t_vars *vars, t_game *game)
{
	t_ray_cast	rc;

	rc.x = 0;
	while (rc.x < WIDTH)
	{
		calculate_ray_direction(game, rc.x, &rc.rayDirX, &rc.rayDirY,
				&rc.cameraX);
		initialize_ray_position(game, rc.rayDirX, rc.rayDirY, &rc.mapX,
				&rc.mapY, &rc.deltaDistX, &rc.deltaDistY);
		initialize_step_and_sidedist(game, &rc);
		rc.hit = 0;
		process_ray_casting(game, vars, &rc);
		rc.x++;
	}
}

int	render(t_vars *vars)
{
	clear_image(&vars->game->img);
	update_movement(vars->game);
	render_scene(vars, vars->game);
	mlx_put_image_to_window(vars->game->mlx, vars->game->win,
			vars->game->img.img, 0, 0);
	if (BONUS)
		draw_minimap(vars->game);
	if (vars->game->door_cooldown > 0)
		vars->game->door_cooldown--;
	return (0);
}
