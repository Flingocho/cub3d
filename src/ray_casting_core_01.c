#include "../include/cub3d.h"

/**
 * @brief Selects the appropriate door texture based on animation frame
 *
 * Chooses one of four door textures based on the animation counter value.
 * This creates an animated door effect when doors are rendered in the game.
 * The textures cycle through DOOR1, DOOR2, DOOR3, and DOOR4 in sequence.
 *
 * @param game Game structure containing the texture arrays
 * @param i Animation counter value determining which texture to select
 * @param texture Pointer to texture that will be set to the selected door texture
 */
static void	select_door_tex(t_game *game, int i, t_img *texture)
{
	if (i <= 10000)
		*texture = game->textures[DOOR1];
	else if (i <= 20000)
		*texture = game->textures[DOOR2];
	else if (i <= 30000)
		*texture = game->textures[DOOR3];
	else if (i <= 40000)
		*texture = game->textures[DOOR4];
}

/**
 * @brief Selects the appropriate texture based on wall orientation or special blocks
 *
 * Determines which texture to use for rendering the current wall segment:
 * - For doors (value 2), selects an animated door texture
 * - For vertical walls (side == 1), selects north or south texture based on ray direction
 * - For horizontal walls (side == 0), selects east or west texture based on ray direction
 * Maintains a static counter for door animations.
 *
 * @param game Game structure containing the texture arrays and world map
 * @param rc Raycasting information including hit position and direction
 * @param texture Pointer to texture that will be set to the selected wall texture
 */
static void	select_texture(t_game *game, t_ray_cast *rc, t_img *texture)
{
	static int	i;

	if (game->world_map[rc->map_y][rc->map_x] == 2)
	{
		if (i >= 40000)
			i = 0;
		select_door_tex(game, i, texture);
	}
	else if (rc->side == 1)
	{
		if (rc->ray_dir_y < 0)
			*texture = game->textures[NORTH];
		else
			*texture = game->textures[SOUTH];
	}
	else
	{
		if (rc->ray_dir_x < 0)
			*texture = game->textures[WEST];
		else
			*texture = game->textures[EAST];
	}
	i++;
}

/**
 * @brief Calculates the perpendicular distance to the wall hit by the ray
 *
 * Computes the distance from the camera plane to the wall hit point, 
 * perpendicular to the camera plane rather than the actual ray length.
 * This prevents the fisheye effect by normalizing distances based on
 * the viewing angle. The calculation method differs depending on whether
 * the ray hit a vertical (side == 1) or horizontal (side == 0) wall face.
 *
 * @param game Game structure containing player position
 * @param rc Raycasting information including hit position and direction
 * @return The perpendicular distance to the wall hit point
 */
static double	calculate_perp_wall_dist(t_game *game, t_ray_cast *rc)
{
	double	perp_wall_dist;
	double	adjustment;

	if (rc->side == 0)
	{
		adjustment = 1;
		if (rc->ray_dir_x < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_x - game->player_x + (1 - adjustment) / 2)
			/ rc->ray_dir_x;
	}
	else
	{
		adjustment = 1;
		if (rc->ray_dir_y < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_y - game->player_y + (1 - adjustment) / 2)
			/ rc->ray_dir_y;
	}
	return (perp_wall_dist);
}

/**
 * @brief Calculates parameters needed for wall rendering
 *
 * Determines the height of the wall slice to be drawn, along with
 * the starting and ending Y-coordinates on the screen. Also clamps
 * these values to ensure they remain within screen boundaries.
 * The wall height is inversely proportional to the distance from the player.
 *
 * @param game Game structure containing the world map
 * @param rc Raycasting information including hit position
 * @param rcw Structure to store calculated wall rendering parameters
 */
static void	calculate_wall_params(t_game *game, t_ray_cast *rc,
		t_ray_cast_draw *rcw)
{
	rcw->perp_wall_dist = calculate_perp_wall_dist(game, rc);
	rcw->line_height = (int)(HEIGHT / rcw->perp_wall_dist);
	rcw->draw_start = (HEIGHT - rcw->line_height) / 2;
	rcw->draw_end = (HEIGHT + rcw->line_height) / 2;
	if (rcw->draw_start < 0)
		rcw->draw_start = 0;
	if (rcw->draw_end >= HEIGHT)
		rcw->draw_end = HEIGHT - 1;
	rcw->tex_num = game->world_map[rc->map_y][rc->map_x] - 1;
}

/**
 * @brief Renders a single vertical column of the screen
 *
 * Orchestrates the rendering process for a single screen column:
 * 1. Calculates wall dimensions and position
 * 2. Selects the appropriate texture based on wall orientation
 * 3. Calculates texture coordinates for mapping
 * 4. Draws the wall column with the proper texture
 * 5. Draws the ceiling and floor for this column
 *
 * @param game Game structure containing rendering context and world map
 * @param vars Main program variables structure
 * @param rc Raycasting information for the current column
 */
void	render_column(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	t_ray_cast_draw	rcw;
	t_img			texture;

	calculate_wall_params(game, rc, &rcw);
	select_texture(game, rc, &texture);
	calculate_texture_coordinates(game, rc, &rcw, &texture);
	draw_wall_column(game, rc, &rcw, &texture);
	draw_ceiling_and_floor(rc, &rcw, vars);
}
