#include "../include/cub3d.h"

/**
 * @brief Implements the Digital Differential Analysis (DDA) algorithm for ray casting
 *
 * A grid traversal algorithm that efficiently finds where a ray intersects
 * with a wall in the grid-based world map. It steps through the grid cells
 * in the ray's direction until it hits a non-empty space (wall or door).
 * The algorithm tracks which face of the wall (horizontal or vertical) was hit.
 *
 * @param game Game structure containing the world map
 * @param rc Raycasting information including ray direction and position
 */
static void	perform_dda(t_game *game, t_ray_cast *rc)
{
	while (!(rc->hit))
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->world_map[rc->map_y][rc->map_x] != 0
			&& game->world_map[rc->map_y][rc->map_x] != 3)
			rc->hit = 1;
	}
}

/**
 * @brief Processes a single ray and renders the corresponding screen column
 *
 * Executes the DDA algorithm to find where the ray hits a wall,
 * then renders the appropriate wall column with texture mapping.
 * This function is called for each vertical column of the screen.
 *
 * @param game Game structure containing the world map and rendering context
 * @param vars Main program variables structure
 * @param rc Raycasting information for the current ray/column
 */
void	process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	perform_dda(game, rc);
	render_column(game, vars, rc);
}

/**
 * @brief Initializes step direction and side distance values for DDA algorithm
 *
 * Sets up the values needed for the DDA ray traversal:
 * - Determines step direction (1 or -1) in both x and y axes based on ray direction
 * - Calculates initial side distances, which represent how far along the ray we need
 *   to travel to cross the first grid cell boundary in x and y directions
 *
 * @param game Game structure containing player position
 * @param rc Raycasting information to be initialized with step and side distance values
 */
void	initialize_step_and_sidedist(t_game *game, t_ray_cast *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player_y) * rc->delta_dist_y;
	}
}

/**
 * @brief Initializes ray position and delta distance values
 *
 * Sets up the initial ray position in the grid and calculates delta distance values.
 * Delta distances represent how far along the ray we need to travel to cross a grid
 * cell boundary on the x or y axis. These values are used by the DDA algorithm to
 * efficiently traverse the grid.
 *
 * @param game Game structure containing player position
 * @param rc Raycasting information to be initialized with position and delta values
 */
void	initialize_ray_position(t_game *game, t_ray_cast *rc)
{
	rc->map_x = (int)game->player_x;
	rc->map_y = (int)game->player_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

/**
 * @brief Calculates the direction vector for a ray
 *
 * Determines the direction vector for the current ray based on the player's
 * direction, camera plane, and the position of the ray in screen space.
 * The camera_x value maps the screen x-coordinate to the range [-1, 1],
 * representing the position on the camera plane.
 *
 * @param game Game structure containing player direction and camera plane
 * @param rc Raycasting information including the screen x-coordinate
 */
void	calculate_ray_direction(t_game *game, t_ray_cast *rc)
{
	rc->camera_x = 2 * rc->x / (double)WIDTH - 1;
	rc->ray_dir_x = game->dir_x + game->plane_x * (rc->camera_x);
	rc->ray_dir_y = game->dir_y + game->plane_y * (rc->camera_x);
}
