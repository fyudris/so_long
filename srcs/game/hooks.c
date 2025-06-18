/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:10:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 21:10:07 by fyudris          ###   ########.fr       */
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
 * This function now includes collision detection and updates the animation state
 * (direction and is_moving flag) in addition to moving the player. This
 * fulfills the mandatory requirement for W, A, S, D movement and ESC exit.
 */
int	handle_keypress(int keycode, t_data *data)
{
	t_vector	next_pos;

	if (keycode == KEY_ESC)
		cleanup_and_exit(data, 0);
	// Determine the potential next position based on input
	next_pos = data->player_pos;
	if (keycode == KEY_W)
		next_pos.y -= 1;
	else if (keycode == KEY_A)
		next_pos.x -= 1;
	else if (keycode == KEY_S)
		next_pos.y += 1;
	else if (keycode == KEY_D)
		next_pos.x += 1;
	// Check for collision with an impassable Fort wall ('1')
	if (data->map.grid[next_pos.y][next_pos.x] == '1')
		return (0); // If collision, do nothing.
	// If move is valid, update state
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		data->player_pos = next_pos;
		data->is_moving = true;
		if (keycode == KEY_W)
			data->player_dir = UP;
		else if (keycode == KEY_A)
			data->player_dir = LEFT;
		else if (keycode == KEY_S)
			data->player_dir = DOWN;
		else if (keycode == KEY_D)
			data->player_dir = RIGHT;
		data->move_count++;
		ft_printf("Move count: %d\n", data->move_count);
	}
	return (0);
}
