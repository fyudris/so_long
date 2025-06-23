/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:16:30 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 16:16:32 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	init_game_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->player_dir = RIGHT;
}

void	init_mlx(t_data *data)
{
	int	win_width;
	int	win_height;

	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(data, 1);
	win_width = data->map.size.x * TILE_SIZE;
	// Mandatory window height does NOT include a UI bar.
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
