/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 19:35:20 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief A helper function to draw the correct tile based on the map character.
 *
 * This function simplifies the main render loop by containing the logic for
 * which texture corresponds to which character on the map grid.
 *
 * @param data The main data struct.
 * @param x The x-coordinate (in tiles) to draw at.
 * @param y The y-coordinate (in tiles) to draw at.
 */
static void	draw_tile(t_data *data, int x, int y)
{
	char	tile_type;
	void	*img_ptr;

	tile_type = data->map.grid[y][x];
	img_ptr = NULL;
	if (tile_type == '1')
		img_ptr = data->textures.fort_wall.ptr;
	// else if (tile_type == 'C')
	// 	img_ptr = data->textures.key_item.ptr;
	// else if (tile_type == 'E')
	// 	img_ptr = data->textures.exit_door.ptr;
	// else if (tile_type == 'W')
	// 	img_ptr = data->textures.wall_obj.ptr;
	// Add else-if statements for ALL your other map characters ('D', 'k', 'i', etc.)

	if (img_ptr)
		mlx_put_image_to_window(data->mlx, data->win, img_ptr,
			x * TILE_SIZE, y * TILE_SIZE);
}

/**
 * @brief The main rendering function, called on every frame by the MLX loop
 * hook.
 *
 * This function is the "heartbeat" of the game's visuals. It clears the
 * window and then redraws the entire game state - the map and the player.
 *
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	render_frame(t_data *data)
{
	int	x;
	int	y;

	// Optional: Clear the window to a single color first. Not strictly needed
	// if your map covers the entire screen.
	// mlx_clear_window(data->mlx, data->win);

	// 1. Draw the static map background and objects
	y = 0;
	while (y < data->map.size.y)
	{
		x = 0;
		while (x < data->map.size.x)
		{
			draw_tile(data, x, y);
			x++;
		}
		y++;
	}

	// 2. Draw the player on top of the map
	mlx_put_image_to_window(data->mlx, data->win, data->textures.player.ptr,
		data->player_pos.x * TILE_SIZE, data->player_pos.y * TILE_SIZE);
	return (0);
}