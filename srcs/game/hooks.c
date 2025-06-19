/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:10:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/19 17:56:41 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Handles the event when the window's close button (red 'X') is clicked.
 *
 * This is a mandatory feature for a clean exit.
 *
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	handle_close_window(t_data *data)
{
	ft_printf("Closing window...\n");
	cleanup_and_exit(data, 0);
	return (0);
}

static bool	is_pushable(char tile)
{
	// Define all characters that the player can push     
	if (ft_strchr("WRcuwryniso", tile)) // Before: "pkeuryniswos"
		return (true);
	return (false);
}

/**
 * @brief Handles the event when a movement key is RELEASED.
 * This is crucial for stopping the walking animation and returning to an idle 
 * pose.
 */
int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		data->is_moving = false;
		// Reset to the first frame (the idle pose) when movement stops.
		data->anim_frame = 0;
	}
	return (0);
}

/**
 * @brief Handles all keyboard PRESS events.
 *
 * This function has been re-ordered to first update the player's intended
 * direction, and then use that direction to correctly resolve collisions
 * and push mechanics.
 */
/**
 * @brief Handles all keyboard PRESS events with the correct order of operations.
 */
/**
 * @brief Handles all keyboard PRESS events with a robust, correctly-ordered logic.
 *
 * This function ensures that movement is only blocked if a specific, invalid
 * condition is met (hitting a wall, a locked exit, or a failed push).
 * A move into an empty '0' tile will always succeed.
 */
int	handle_keypress(int keycode, t_data *data)
{
	t_vector	next_pos;
	char		next_tile;

	if (keycode == KEY_ESC)
		cleanup_and_exit(data, 0);
	if (keycode != KEY_W && keycode != KEY_A && keycode != KEY_S && keycode != KEY_D)
		return (0);

	// 1. Set player's intended direction immediately. This is crucial.
	data->is_moving = true;
	if (keycode == KEY_W)
		data->player_dir = UP;
	else if (keycode == KEY_A)
		data->player_dir = LEFT;
	else if (keycode == KEY_S)
		data->player_dir = DOWN;
	else if (keycode == KEY_D)
		data->player_dir = RIGHT;
	
	// 2. Calculate the potential destination tile
	next_pos = data->player_pos;
	if (data->player_dir == UP)
		next_pos.y -= 1;
	else if (data->player_dir == DOWN)
		next_pos.y += 1;
	else if (data->player_dir == LEFT)
		next_pos.x -= 1;
	else if (data->player_dir == RIGHT)
		next_pos.x += 1;

	// 3. Check for blocking conditions.
	next_tile = data->map.grid[next_pos.y][next_pos.x];
	if (next_tile == '1') // Condition A: Is it an impassable Fort wall?
		return (0);
	else if (next_tile == 'E' && data->keys_collected < data->map.collectibles) // Condition B: Is it a locked Exit?
		return (0);
	else if (is_pushable(next_tile)) // Condition C: Is it a pushable object?
	{
		if (!handle_push(data, next_pos)) // Try to push it.
			return (0); // If the push fails, block the move.
	}
	
	// 4. If NONE of the blocking conditions were met, the move is valid.
	// This includes moving into an empty '0' or onto a collectible 'C'.
	if (next_tile == 'C')
	{
		// TODO: Implement your KEY IS OPEN logic check here.
		// For now, let's just collect it.
		data->keys_collected++;
		data->map.grid[next_pos.y][next_pos.x] = '0'; // Remove the key
	}
	data->player_pos = next_pos; // Update player position
	data->move_count++;
	ft_printf("Move count: %d\n", data->move_count);
	return (0);
}

