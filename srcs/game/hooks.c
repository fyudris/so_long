/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:10:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 19:19:04 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief A centralized cleanup function to free all allocated memory.
 *
 * This function should be called before the program exits to prevent memory
 * leaks.
 * It destroys all loaded MLX images and windows and frees the map grid.
 *
 * @param data A pointer to the main game data struct.
 */
static void	cleanup_and_exit(t_data *data)
{
	// This is a partial list. You must destroy EVERY image you loaded.
	if (data->textures.player.ptr)
		mlx_destroy_image(data->mlx, data->textures.player.ptr);
	if (data->textures.fort_wall.ptr)
		mlx_destroy_image(data->mlx, data->textures.fort_wall.ptr);
	// ... destroy all other textures ...

	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	// TODO: You should also have a function to free your char** map.grid
	// free_map(data->map.grid);
	exit(0);
}

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
	cleanup_and_exit(data);
	return (0);
}

/**
 * @brief Handles all keyboard press events.
 *
 * This function checks for the ESC key to close the game and the
 * W, A, S, D keys for player movement. This fulfills a mandatory part
 * of the project.
 *
 * @param keycode The integer code of the key that was pressed.
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	handle_keypress(int keycode, t_data *data)
{
	// Handle exiting the game
	if (keycode == KEY_ESC)
	{
		ft_printf("ESC key pressed. Exiting...\n");
		cleanup_and_exit(data);
	}

	// Handle player movement
	if (keycode == KEY_W)
		data->player_pos.y -= 1;
	else if (keycode == KEY_A)
		data->player_pos.x -= 1;
	else if (keycode == KEY_S)
		data->player_pos.y += 1;
	else if (keycode == KEY_D)
		data->player_pos.x += 1;

	// If a movement key was pressed, print the move count to the shell
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		data->move_count++;
		ft_printf("Move count: %d\n", data->move_count);
	}
	return (0);
}