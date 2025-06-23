/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:10:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/21 01:01:08 by fyudris          ###   ########.fr       */
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

/**
 * @brief Helper to check if a tile represents a pushable object.
 * This now checks the rules struct for objects like walls.
 */
static bool	is_pushable(t_data *data, char tile)
{// Text blocks are always pushable.
	if (ft_strchr("pcewrynisuo", tile))
		return (true);
	// Game objects are only pushable if the rule is active.
	if (tile == 'W' && data->rules.wall_is_pushable == true)
		return (true);
	if (tile == 'R' && data->rules.rock_is_pushable == true)
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
 * @brief Handles all keyboard PRESS events with the final, robust logic.
 *
 * This function is ordered to prevent common state bugs. It updates the
 * player's intended direction first, then checks for all blocking conditions
 * (walls, locked objects, failed pushes) before committing to a move.
 *
 * @param keycode The integer code of the key that was pressed.
 * @param data A pointer to the main game data struct.
 * @return int Always returns 0.
 */
int	handle_keypress(int keycode, t_data *data)
{
	t_vector	next_pos;
	char		next_tile;

	if (keycode == KEY_ESC)
		cleanup_and_exit(data, 0);
	if (keycode != KEY_W && keycode != KEY_A && keycode != KEY_S && keycode != KEY_D)
		return (0);
	// 1. Set player's intended direction and state immediately.
	data->is_moving = true;
	if (keycode == KEY_W)
		data->player_dir = UP;
	else if (keycode == KEY_A)
		data->player_dir = LEFT;
	else if (keycode == KEY_S)
		data->player_dir = DOWN;
	else if (keycode == KEY_D)
		data->player_dir = RIGHT;
	// 2. Calculate the destination tile based on the NEW direction.
	next_pos = data->player_pos;
	if (data->player_dir == UP)
		next_pos.y -= 1;
	else if (data->player_dir == DOWN)
		next_pos.y += 1;
	else if (data->player_dir == LEFT)
		next_pos.x -= 1;
	else if (data->player_dir == RIGHT)
		next_pos.x += 1;
	// 3. Handle all interactions and blocking conditions.
	next_tile = data->map.grid[next_pos.y][next_pos.x];
	
	// --- Blocking Conditions ---
	if (next_tile == '1')
		return (0); // Blocked by Fort wall
	if ((next_tile == 'W' && !data->rules.wall_is_pushable))
		return (0); // Blocked by a solid Wall object
	if ((next_tile == 'R' && !data->rules.rock_is_pushable))
		return (0); // Blocked by a solid Rock object
	if (is_pushable(data, next_tile))
	{
		if (!handle_push(data, next_pos)) // If a push fails, block the move.
			return (0);
	}

	// --- Win Condition Check (The Triple Lock) ---
	if (next_tile == 'E')
	{
		// Check for ALL THREE conditions to win
		if (data->keys_collected >= data->map.collectibles
			&& data->rules.key_is_activated == true)
		{
			ft_printf("YOU WIN! Final moves: %d\n", data->move_count + 1);
			cleanup_and_exit(data, 0);
		}
		// If any condition is false, the Exit is just a solid wall.
		return (0);
	}

	// 4. Handle collecting a key (No preconditions needed).
	if (next_tile == 'C')
	{
		data->keys_collected++;
		data->map.grid[next_pos.y][next_pos.x] = '0'; // Remove key from map
		ft_printf("Key collected! Total: %d of %d\n",
			data->keys_collected, data->map.collectibles);
	}

	// 5. If no blocking conditions were met, finalize the move.
	data->player_pos = next_pos;
	data->move_count++;
	ft_printf("Move count: %d\n", data->move_count);
	return (0);
}


