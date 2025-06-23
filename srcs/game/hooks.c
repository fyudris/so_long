/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:25:21 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 15:38:32 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	handle_close_window(t_data *data)
{
	cleanup_and_exit(data, 0);
	return (0);
}

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
	if (data->map.grid[next_pos.y][next_pos.x] == '1')
		return (0);
	if (data->map.grid[next_pos.y][next_pos.x] == 'E')
	{
		if (data->keys_collected >= data->map.collectibles)
		{
			ft_printf("You Win!\nTotal moves: %d\n", data->move_count + 1);
			cleanup_and_exit(data, 0);
		}
		return (0);
	}
	if (data->map.grid[next_pos.y][next_pos.x] == 'C')
	{
		data->keys_collected++;
		data->map.grid[next_pos.y][next_pos.x] = '0';
	}
	data->player_pos = next_pos;
	data->move_count++;
	ft_printf("Move count: %d\n", data->move_count);
	return (0);
}
