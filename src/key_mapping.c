#include "../include/cub3d.h"

/**
 * @brief Handle window close event
 * 
 * This function is called when the window close button is clicked or
 * when the escape key is pressed. It performs proper cleanup and exits
 * the program gracefully.
 * 
 * @param vars The main program structure
 * @return Always returns 0
 */
int	close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}

/**
 * @brief Handle door interaction
 * 
 * This function toggles doors adjacent to the player between opened (3)
 * and closed (2) state when the player presses the interaction key.
 * A cooldown is implemented to prevent rapid door toggling.
 * 
 * @param game Pointer to the game structure
 */
static void	manage_door(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = (int)game->player_x;
	player_y = (int)game->player_y;
	if (game->door_cooldown > 0)
		return ;
	if (game->world_map[player_y][player_x + 1] == 2)
		game->world_map[player_y][player_x + 1] = 3;
	else if (game->world_map[player_y][player_x - 1] == 2)
		game->world_map[player_y][player_x - 1] = 3;
	else if (game->world_map[player_y + 1][player_x] == 2)
		game->world_map[player_y + 1][player_x] = 3;
	else if (game->world_map[player_y - 1][player_x] == 2)
		game->world_map[player_y - 1][player_x] = 3;
	else if (game->world_map[player_y][player_x + 1] == 3)
		game->world_map[player_y][player_x + 1] = 2;
	else if (game->world_map[player_y][player_x - 1] == 3)
		game->world_map[player_y][player_x - 1] = 2;
	else if (game->world_map[player_y + 1][player_x] == 3)
		game->world_map[player_y + 1][player_x] = 2;
	else if (game->world_map[player_y - 1][player_x] == 3)
		game->world_map[player_y - 1][player_x] = 2;
	game->door_cooldown = 5;
}

/**
 * @brief Update player movement based on active keys
 * 
 * This function is called each frame to process player movements
 * based on which keys are currently being pressed. It handles
 * movement in all directions, rotation, and door interaction.
 * 
 * @param game Pointer to the game structure
 */
void	update_movement(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_d)
		move_right(game);
	if (game->key_a)
		move_left(game);
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
	if (BONUS && game->key_e)
		manage_door(game);
}

/**
 * @brief Handle key press events
 * 
 * This callback function is triggered when a key is pressed. It updates
 * the state of movement keys and handles special actions like exiting
 * the program when ESC is pressed.
 * 
 * @param key The keycode of the pressed key
 * @param vars The main program structure
 * @return Always returns 0
 */
int	key_press(int key, t_vars *vars)
{
	if (key == 65307)
		close_window(vars);
	if (key == 119)
		vars->game->key_w = 1;
	if (key == 115)
		vars->game->key_s = 1;
	if (key == 97)
		vars->game->key_a = 1;
	if (key == 100)
		vars->game->key_d = 1;
	if (key == 65361)
		vars->game->key_left = 1;
	if (key == 65363)
		vars->game->key_right = 1;
	if (BONUS && key == 101)
		vars->game->key_e = 1;
	return (0);
}

/**
 * @brief Handle key release events
 * 
 * This callback function is triggered when a key is released. It updates
 * the state of movement keys, resetting them to their inactive state.
 * 
 * @param key The keycode of the released key
 * @param game Pointer to the game structure
 * @return Always returns 0
 */
int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->key_w = 0;
	if (key == 115)
		game->key_s = 0;
	if (key == 97)
		game->key_a = 0;
	if (key == 100)
		game->key_d = 0;
	if (key == 65361)
		game->key_left = 0;
	if (key == 65363)
		game->key_right = 0;
	if (BONUS && key == 101)
		game->key_e = 0;
	return (0);
}
