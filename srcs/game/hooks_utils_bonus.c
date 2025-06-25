/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:52 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:31:00 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hooks_utils_bonus.c
 * @brief Utility functions for the bonus event hooks.
 * @details This file contains the helper functions called by handle_keypress
 * to keep the main hook file clean and compliant with the Norm.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Updates the player's direction based on the key pressed.
 */
void	update_player_direction(int keycode, t_data *data)
{
	data->is_moving = true;
	if (keycode == KEY_W)
		data->player_dir = UP;
	else if (keycode == KEY_A)
		data->player_dir = LEFT;
	else if (keycode == KEY_S)
		data->player_dir = DOWN;
	else if (keycode == KEY_D)
		data->player_dir = RIGHT;
}

/**
 * @brief Checks for collisions and handles push mechanics.
 * @return `true` if the player's path is blocked, `false` otherwise.
 */
bool	check_collisions(t_data *data, t_vector next_pos)
{
	char	next_tile;

	next_tile = data->map.grid[next_pos.y][next_pos.x];
	if (next_tile == '1')
		return (true);
	if (next_tile == 'W' && !data->rules.wall_is_pushable)
		return (true);
	if (next_tile == 'R' && !data->rules.rock_is_pushable)
		return (true);
	if (is_pushable(data, next_tile))
	{
		if (!handle_push(data, next_pos))
			return (true);
	}
	return (false);
}

/**
 * @brief Processes interactions with collectibles and the exit.
 * @return `true` if the game should end (win or locked exit), `false` otherwise.
 */
bool	process_interactions(t_data *data, t_vector next_pos)
{
	char	next_tile;

	next_tile = data->map.grid[next_pos.y][next_pos.x];
	if (next_tile == 'E')
	{
		if (data->keys_collected >= data->map.collectibles
			&& data->rules.key_is_activated == true)
		{
			ft_printf("YOU WIN! Final moves: %d\n", data->move_count + 1);
			cleanup_and_exit(data, 0);
		}
		return (true);
	}
	if (next_tile == 'C')
	{
		data->keys_collected++;
		data->map.grid[next_pos.y][next_pos.x] = '0';
		ft_printf("Key collected! Total: %d of %d\n",
			data->keys_collected, data->map.collectibles);
	}
	return (false);
}

/**
 * @brief Finalizes a valid move by updating the player's state.
 */
void	finalize_move(t_data *data, t_vector next_pos)
{
	data->player_pos = next_pos;
	data->move_count++;
	ft_printf("Move count: %d\n", data->move_count);
}
