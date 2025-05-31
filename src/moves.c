#include "../include/cub3d.h"

/**
 * @brief Rotates the player's view direction and camera plane
 *
 * Applies a rotation transformation to the player's direction vector
 * and camera plane to change the viewing angle. Uses trigonometric
 * functions to calculate the new vectors based on the input angle.
 *
 * @param game Game structure containing player direction and plane vectors
 * @param angle Rotation angle in radians (positive for clockwise, negative for counterclockwise)
 */
void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

/**
 * @brief Moves the player forward in the direction they're facing
 *
 * Calculates the new position by adding the direction vector multiplied
 * by the movement speed to the current position. Includes collision detection
 * to prevent moving through walls (value 1) while allowing movement through
 * door spaces (value 3). Uses an offset for better collision detection.
 *
 * @param game Game structure containing player position and world map
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x + game->dir_x * MOVE_SPEED;
	new_y = game->player_y + game->dir_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->dir_x < 0)
		offset_x = -0.2;
	if (game->dir_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Moves the player backward, opposite to the direction they're facing
 *
 * Calculates the new position by subtracting the direction vector multiplied
 * by the movement speed from the current position. Includes collision detection
 * to prevent moving through walls (value 1) while allowing movement through
 * door spaces (value 3). Uses an offset for better collision detection.
 *
 * @param game Game structure containing player position and world map
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x - game->dir_x * MOVE_SPEED;
	new_y = game->player_y - game->dir_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->dir_x < 0)
		offset_x = 0.2;
	if (game->dir_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Strafes the player to the right
 *
 * Moves the player perpendicular to their facing direction by using
 * the camera plane vector. Includes collision detection to prevent 
 * moving through walls (value 1) while allowing movement through
 * door spaces (value 3). Uses an offset for better collision detection.
 *
 * @param game Game structure containing player position and world map
 */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x + game->plane_x * MOVE_SPEED;
	new_y = game->player_y + game->plane_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->plane_x < 0)
		offset_x = -0.2;
	if (game->plane_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Strafes the player to the left
 *
 * Moves the player perpendicular to their facing direction by using
 * the inverse of the camera plane vector. Includes collision detection 
 * to prevent moving through walls (value 1) while allowing movement through
 * door spaces (value 3). Uses an offset for better collision detection.
 *
 * @param game Game structure containing player position and world map
 */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = game->player_x - game->plane_x * MOVE_SPEED;
	new_y = game->player_y - game->plane_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->plane_x < 0)
		offset_x = 0.2;
	if (game->plane_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}
