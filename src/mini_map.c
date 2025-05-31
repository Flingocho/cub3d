#include "../include/cub3d.h"

/**
 * @brief Draws a colored square on the mini-map
 *
 * Renders a square of size TILE_SIZE at the specified position
 * on the mini-map with the given color. Used to represent walls,
 * empty spaces, and the player position.
 *
 * @param game Game structure containing MLX context and window
 * @param x X-coordinate in mini-map grid units
 * @param y Y-coordinate in mini-map grid units
 * @param color RGB color value to fill the square
 */
static void	draw_square(t_game *game, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = MAP_OFFSET + x * TILE_SIZE;
	start_y = MAP_OFFSET + y * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i,
				color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draws all the visible cells in the mini-map
 *
 * Iterates through the portion of the world map that should be visible
 * in the mini-map and renders each cell with appropriate colors:
 * - White (0xFFFFFF) for walls
 * - Black (0x000000) for empty spaces
 *
 * @param game Game structure containing the world map and rendering context
 * @param vals Mini-map boundary values that define the visible area
 */
static void	draw_cells(t_game *game, t_minimap *vals)
{
	int	y;
	int	x;
	int	color;

	y = vals->start_y;
	while (y <= vals->end_y)
	{
		x = vals->start_x;
		while (x <= vals->end_x)
		{
			if (game->world_map[y][x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(game, x - vals->start_x, y - vals->start_y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Ensures mini-map boundaries stay within the valid map area
 *
 * Adjusts the mini-map's visible area boundaries to prevent trying to render
 * areas outside the actual game map. This prevents array access violations
 * and ensures the mini-map correctly handles map edges.
 *
 * @param game Game structure containing map dimension information
 * @param vals Mini-map boundary values to be clamped
 */
static void	clamp_minimap_bounds(t_game *game, t_minimap *vals)
{
	if (vals->start_x < 0)
		vals->start_x = 0;
	if (vals->start_y < 0)
		vals->start_y = 0;
	if (vals->end_x >= game->map_width)
		vals->end_x = game->map_width - 1;
	if (vals->end_y >= game->map_height)
		vals->end_y = game->map_height - 1;
}

/**
 * @brief Main function to render the mini-map
 *
 * Calculates the visible area of the mini-map based on the player's current
 * position and the defined MINIMAP_RADIUS. Ensures the boundaries are valid,
 * draws the map cells, and places a red square (0xFF0000) at the player's position.
 *
 * @param game Game structure containing player position and map data
 */
void	draw_minimap(t_game *game)
{
	t_minimap	vals;

	vals.start_x = (int)(game->player_x) - MINIMAP_RADIUS;
	vals.start_y = (int)(game->player_y) - MINIMAP_RADIUS;
	vals.end_x = (int)(game->player_x) + MINIMAP_RADIUS;
	vals.end_y = (int)(game->player_y) + MINIMAP_RADIUS;
	clamp_minimap_bounds(game, &vals);
	draw_cells(game, &vals);
	draw_square(game, game->player_x - vals.start_x, game->player_y
		- vals.start_y, 0xFF0000);
}
