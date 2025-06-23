/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:10 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 13:00:36 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Initializes the entire data struct to zeros (0, NULL, false).
 *
 */
void	init_game_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

/**
 * @brief Establishes a connection to the graphical server and creates a window.
 *
 * This function calculates the required windw dimensions based on the map size
 * and the defined TILE_SIZE. It exits with an error if MLX fails to init
 * or if the window creation fails.
 *
 * @param data A pointer to the main game data struct.
 */
void	init_mlx(t_data *data)
{
	int	win_width;
	int	win_height;
	int buffer_width;
	int buffer_height;

	data->mlx = mlx_init();
	if (!data->mlx)
		ft_print_error("Failed to initialize MiniLibX.");
	win_width = data->map.size.x * TILE_SIZE;
	win_height = (data->map.size.y * TILE_SIZE) + UI_HEIGHT;
	data->win = mlx_new_window(data->mlx, win_width, win_height, "Baba Is You");
	if (!data->win)
		ft_print_error("Failed to create window.");
	buffer_width = data->map.size.x * TILE_SIZE;
	buffer_height = data->map.size.y * TILE_SIZE;
	data->game_buffer.ptr = mlx_new_image(data->mlx, buffer_width, buffer_height);
	if (!data->game_buffer.ptr)
	{
		ft_printf("Error\nFailed to create game buffer image.\n");
		cleanup_and_exit(data, 1);
	}
	data->game_buffer.addr = mlx_get_data_addr(data->game_buffer.ptr,
		&data->game_buffer.bpp, &data->game_buffer.line_len, &data->game_buffer.endian);
	data->game_buffer.width = buffer_width;
	data->game_buffer.height = buffer_height;
}
