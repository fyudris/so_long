/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:16:30 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:33:27 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init.c
 *
 * @brief Initialization functions for the so_long game.

 * @details This file contains the core functions responsible for setting up
 * the game's initial state, including the main data structure and the
 * connection to the MiniLibX graphical server. This is the MANDATORY
 * version, which does not include a graphical UI bar.
 */
#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Initializes the main game data structure.
 *
 * @details This function takes the primary `t_data` struct and sets all its
 * members to a default state of zero (0, NULL, or false) using `ft_bzero`.
 * It also sets the player's initial facing direction to RIGHT.
 *
 * @param data A pointer to the main `t_data` struct to be initialized.
 */
void	init_game_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->player_dir = RIGHT;
	data->last_time = 0;
}

/**
 * @brief Establishes a connection to the graphical server and creates the game
 * window.
 *
 * @details This function performs several critical setup steps:
 * 	1. Calls `mlx_init()` to establish a connection with the display server.
 * 	2. Calculates the required window dimensions based on the map's grid size
 * and the `TILE_SIZE` constant. For the mandatory part, the window height
 * is strictly the map height with no extra space for a UI.
 * 	3. Calls `mlx_new_window()` to create the on-screen window.
 * 	4. Creates an off-screen image buffer (`game_buffer`) the same size as the
 * window. This buffer is used for double-buffering to prevent flickering.
 * All game elements will be drawn to this buffer first before being pushed
 * to the window in a single operation.
 * 	5. Retrieves the data address and properties of the image buffer, which are
 * necessary for direct pixel manipulation.
 *
 * @param data A pointer to the main `t_data` struct.
 */
void	init_mlx(t_data *data)
{
	int	win_width;
	int	win_height;

	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(data, 1);
	win_width = data->map.size.x * TILE_SIZE;
	win_height = data->map.size.y * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, win_width, win_height, "so_long");
	if (!data->win)
		cleanup_and_exit(data, 1);
	data->game_buffer.ptr = mlx_new_image(data->mlx, win_width, win_height);
	if (!data->game_buffer.ptr)
		cleanup_and_exit(data, 1);
	data->game_buffer.addr = mlx_get_data_addr(data->game_buffer.ptr,
			&data->game_buffer.bpp, &data->game_buffer.line_len,
			&data->game_buffer.endian);
	data->game_buffer.width = win_width;
	data->game_buffer.height = win_height;
}
