/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:25:21 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:57 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file hooks.c
 * @brief Event handling functions for the so_long game (Mandatory).
 * @details This file contains the functions that respond to user input,
 * such as closing the window or pressing a key. It handles the core
 * game logic for player movement in the mandatory version.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void	process_move(t_data *data, t_vector next_pos);
static void	perform_move(t_data *data, t_vector next_pos);

/**
 * @brief Handles the event when the window's close button (red 'X') is clicked.
 *
 * @details This is a mandatory feature for a clean exit. It calls the main
 * cleanup function to free all allocated resources before terminating.
 *
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, 0);
	return (0);
}

/**
 * @brief Processes the outcome of a potential move.
 *
 * @details This function checks the tile at the player's `next_pos`. It handles
 * collisions with walls ('1'), interactions with collectibles ('C'), and checks
 * the win condition at the exit ('E'). If the move is valid, it calls
 * `perform_move` to finalize it.
 *
 * @param data The main game data struct.
 * @param next_pos The coordinates the player is attempting to move to.
 */
static void	process_move(t_data *data, t_vector next_pos)
{
	char	tile_type;

	tile_type = data->map.grid[next_pos.y][next_pos.x];
	if (tile_type == '1')
		return ;
	if (tile_type == 'E')
	{
		if (data->keys_collected >= data->map.collectibles)
		{
			ft_printf("You Win!\nTotal moves: %d\n", data->move_count + 1);
			cleanup_and_exit(data, 0);
		}
		return ;
	}
	if (tile_type == 'C')
	{
		data->keys_collected++;
		data->map.grid[next_pos.y][next_pos.x] = '0';
	}
	perform_move(data, next_pos);
}

/**
 * @brief Updates the player's state after a valid move.
 * @details This helper function is called by `process_move` once a move has
 * been confirmed as valid. It updates the player's position in the data
 * struct, increments the move counter, and prints the new count to the shell
 * as required by the subject.
 *
 * @param data The main game data struct.
 * @param next_pos The new, validated position for the player.
 */
static void	perform_move(t_data *data, t_vector next_pos)
{
	data->player_pos = next_pos;
	data->move_count++;
	ft_printf("Move count: %d\n", data->move_count);
}

/**
 * @brief Handles all keyboard press events.
 *
 * @details This function is the main entry point for user movement. It checks
 * for the ESC key to exit the game. For movement keys (W, A, S, D), it
 * calculates the player's potential next position and then calls
 * `process_move` to handle the logic for that move.
 *
 * @param keycode The integer code of the key that was pressed.
 * @param data A pointer to the main game data struct.
 * @return int Always returns 0.
 */
int	handle_keypress(int keycode, t_data *data)
{
	t_vector	next_pos;

	if (keycode == KEY_ESC)
		cleanup_and_exit(data, 0);
	next_pos = data->player_pos;
	if (keycode == KEY_W)
		next_pos.y -= 1;
	else if (keycode == KEY_A)
		next_pos.x -= 1;
	else if (keycode == KEY_S)
		next_pos.y += 1;
	else if (keycode == KEY_D)
		next_pos.x += 1;
	else
		return (0);
	process_move(data, next_pos);
	return (0);
}
