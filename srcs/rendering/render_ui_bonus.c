/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:42:54 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:48:06 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_ui_bonus.c
 * @brief Utility functions for the bonus UI rendering.
 * @details This file contains helper functions that are called by the main
 * render loop.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Draws the left side of the UI panel (the move counter).
 */
void	draw_ui_left(t_data *data)
{
	if (data->textures.ui_move_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_move_icon.frames[0].ptr, 20, 10);
	if (data->textures.ui_x_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_x_icon.frames[0].ptr, 20 + TILE_SIZE, 10);
	draw_number(data, data->move_count,
		(t_vector){20 + (2 * TILE_SIZE), 10});
}

/**
 * @brief Draws the right side of the UI panel (the key counter).
 */
void	draw_ui_right(t_data *data)
{
	char	*key_str;
	int		key_counter_width;
	int		win_width;

	key_str = ft_itoa(data->keys_collected);
	if (!key_str)
		return ;
	key_counter_width = (TILE_SIZE * 2) + (ft_strlen(key_str) * TILE_SIZE);
	win_width = data->map.size.x * TILE_SIZE;
	if (data->textures.ui_key_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_key_icon.frames[0].ptr,
			win_width - key_counter_width - 20, 10);
	if (data->textures.ui_x_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_x_icon.frames[0].ptr,
			win_width - key_counter_width - 20 + TILE_SIZE, 10);
	draw_number(data, data->keys_collected,
		(t_vector){win_width - key_counter_width - 20 + (2 * TILE_SIZE), 10});
	free(key_str);
}
