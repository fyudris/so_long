/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:23:22 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/19 15:45:45 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Handles the logic for pushing an object.
 *
 * Checks if the space behind the object is empty. If it is, it moves
 * the object in the map grid.
 *
 * @param data The main data struct.
 * @param obj_pos The current position of the object to be pushed.
 * @param next_pos The position the player is trying to move into (same as obj_pos).
 * @return true if the push was successful, false otherwise.
 */
/**
 * @brief Handles the logic for pushing an object.
 *
 * This function is now safer. It first checks if the destination "behind"
 * the object is within the map boundaries. Only then does it check if that
 * tile is empty. This prevents out-of-bounds memory access and crashes.
 *
 * @param data The main data struct.
 * @param obj_pos The current position of the object to be pushed.
 * @return true if the push was successful, false otherwise.
 */
bool	handle_push(t_data *data, t_vector obj_pos)
{
	t_vector	behind_pos;
	char		obj_char;

	// Calculate the position behind the object, based on player's direction
	behind_pos = obj_pos;
	if (data->player_dir == UP)
		behind_pos.y -= 1;
	else if (data->player_dir == DOWN)
		behind_pos.y += 1;
	else if (data->player_dir == LEFT)
		behind_pos.x -= 1;
	else if (data->player_dir == RIGHT)
		behind_pos.x += 1;
		
	// --- NEW BOUNDARY CHECKS ---
	// First, check if the destination is even on the map.
	if (behind_pos.y < 0 || behind_pos.y >= data->map.size.y
		|| behind_pos.x < 0 || behind_pos.x >= data->map.size.x)
	{
		return (false); // Cannot push an object out of the world.
	}
	// --- END OF NEW CHECKS ---

	// Now that we know the coordinate is safe, check if the tile is empty.
	if (data->map.grid[behind_pos.y][behind_pos.x] == '0')
	{
		// Move the object in the grid
		obj_char = data->map.grid[obj_pos.y][obj_pos.x];
		data->map.grid[behind_pos.y][behind_pos.x] = obj_char;
		data->map.grid[obj_pos.y][obj_pos.x] = '0';
		return (true); // Push was successful
	}
	// The space behind was not empty (e.g., another rock, a wall, etc.)
	return (false);
}
