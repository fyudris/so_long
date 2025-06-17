/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:10 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 18:53:59 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

	data->mlx = mlx_init();
	if (!data->mlx)
		ft_print_error("Failed to initialize MiniLibX.");
	win_width = data->map.size.x * TILE_SIZE;
	win_height = data->map.size.y * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, win_width, win_height, "Baba Is You");
	if (!data->win)
		ft_print_error("Failed to create window.");
}
