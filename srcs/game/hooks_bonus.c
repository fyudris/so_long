/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:10:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:20:30 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hooks_bonus.c
 * @brief Main event hooks for the BONUS version of so_long.
 * @details This file is responsible for receiving raw user input (keypresses,
 * window closing) and orchestrating the calls to helper functions
 * that implement the actual game logic.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Handles the window's close button event.
 */
int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, 0);
	return (0);
}

/**
 * @brief Handles the key release event to stop animations.
 */
int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
	{
		data->is_moving = false;
		data->anim_frame = 0;
	}
	return (0);
}

/**
 * @brief Handles all keyboard PRESS events (Main Entry Point).
 * @details This function now orchestrates the move by calling a sequence
 * of helper functions, each with a single responsibility. This keeps the
 * function short and compliant with the Norm.
 */
int	handle_keypress(int keycode, t_data *data)
{
	t_vector	next_pos;

	if (keycode == KEY_ESC)
		cleanup_and_exit(data, 0);
	if (keycode != KEY_W && keycode != KEY_A
		&& keycode != KEY_S && keycode != KEY_D)
		return (0);
	update_player_direction(keycode, data);
	next_pos = data->player_pos;
	if (data->player_dir == UP)
		next_pos.y -= 1;
	else if (data->player_dir == DOWN)
		next_pos.y += 1;
	else if (data->player_dir == LEFT)
		next_pos.x -= 1;
	else if (data->player_dir == RIGHT)
		next_pos.x += 1;
	if (check_collisions(data, next_pos))
		return (0);
	if (process_interactions(data, next_pos))
		return (0);
	finalize_move(data, next_pos);
	return (0);
}
