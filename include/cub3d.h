/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:42:01 by jvidal-t          #+#    #+#             */
/*   Updated: 2025/02/15 16:06:01 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBS
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// OWN .H
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include "structs.h"
# include "vals.h"

// SRC
// init_vars.c
void	init_vars(t_vars **vars);
// check_args_01.c
int		check_args(int argc, char *argv[], t_vars *vars);
// check_args_02.c
void	read_fd_file(t_vars *vars);
int		check_map_exists(char *path, t_vars *vars);
// check_args_03.c
void	parse_file(t_vars *vars);
// check_args_04.c
void	assign_colors(t_vars *vars);
// check_map_01.c
int		check_map_valid(t_vars *vars);
// check_map_02.c
int		check_valid_charset(t_vars *vars, char c, int i, int j);
// check_map_03.c
int		check_flood(t_vars *vars);
// load_textures.c
int		load_textures(t_vars *vars);
// load_textures_bonus.c
int		load_textures_bonus(t_vars *vars);
// key_mapping.c
int		close_window(t_vars *vars);
void	update_movement(t_game *game);
int		key_press(int key, t_vars *vars);
int		key_release(int key, t_game *game);
// moves.c
void	rotate_player(t_game *game, double angle);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
// ray_casting_00.c
int		render(t_vars *vars);
// ray_casting_init.c
void	process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc);
void	initialize_step_and_sidedist(t_game *game, t_ray_cast *rc);
void	initialize_ray_position(t_game *game, t_ray_cast *rc);
void	calculate_ray_direction(t_game *game, t_ray_cast *rc);
// ray_casting_core_01.c
void	render_column(t_game *game, t_vars *vars, t_ray_cast *rc);
// ray_casting_core_02.c
void	draw_ceiling_and_floor(t_ray_cast *rc,
			t_ray_cast_draw *rcw, t_vars *vars);
void	draw_wall_column(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw,
			t_img *texture);
void	calculate_texture_coordinates(t_game *game, t_ray_cast *rc,
			t_ray_cast_draw *rcw, t_img *texture);
// ray_casting_utils.c
void	put_pixel_fog_floor(t_vars *vars, int x, int y, double fogDistance);
void	put_pixel_fog_ceiling(t_vars *vars, int x, int y, double fogDistance);
void	put_pixel_fog_walls(t_img *img, int x, t_ray_cast_draw *rcw);
// mini_map.c
void	draw_minimap(t_game *game);
// cleaner.c
void	clean_exit(t_vars *vars);
//cleaner_utils.c
void	free_char_matrix(char **mtx);
void	free_int_matrix(t_vars *vars, int **mtx);
void	free_paths(t_vars *vars);
void	free_colors(t_vars *vars);
void	free_textures(t_game *game);

#endif