/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:37:51 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 15:37:52 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static t_animation	*get_tile_animation(t_data *data, char tile_type);
static t_animation	*get_current_player_anim(t_data *data);
static void			draw_map_to_buffer(t_data *data);

/**
 * @brief The main rendering function for the mandatory part.
 */
int	render_frame(t_data *data)
{
	t_animation	*player_anim;

	// Update animation timers for simple sprite effects
	data->anim_timer++;
	if (data->anim_timer >= ANIMATION_SPEED)
	{
		data->anim_timer = 0;
		data->anim_frame++;
	}
	// Clear the back buffer to prevent after-images
	clear_image_buffer(&data->game_buffer, 0x000000);
	// Draw the map and player to the buffer
	draw_map_to_buffer(data);
	player_anim = get_current_player_anim(data);
	if (player_anim && player_anim->frames)
	{
		// Mandatory player has no complex animation, always draw frame 0
		draw_sprite_to_buffer(&data->game_buffer,
			&player_anim->frames[0],
			(t_vector){data->player_pos.x * TILE_SIZE,
			data->player_pos.y * TILE_SIZE});
	}
	// Push the completed game buffer to the window in ONE call
	mlx_put_image_to_window(data->mlx, data->win, data->game_buffer.ptr, 0, 0);
	return (0);
}

static void	draw_map_to_buffer(t_data *data)
{
	int			x;
	int			y;
	t_animation	*anim;

	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			anim = get_tile_animation(data, data->map.grid[y][x]);
			if (anim && anim->frames)
			{
				draw_sprite_to_buffer(&data->game_buffer, &anim->frames[0],
					(t_vector){x * TILE_SIZE, y * TILE_SIZE});
			}
		}
	}
}

/**
 * @brief Returns the animation for mandatory map characters.
 */
static t_animation	*get_tile_animation(t_data *data, char tile_type)
{
	if (tile_type == '1')
		return (&data->textures.fort_wall);
	if (tile_type == 'C')
		return (&data->textures.key);
	if (tile_type == 'E')
		return (&data->textures.door);
	return (NULL);
}

/**
 * @brief Selects the correct player animation sequence based on direction.
 */
static t_animation	*get_current_player_anim(t_data *data)
{
	if (data->player_dir == UP)
		return (&data->textures.player_up);
	if (data->player_dir == DOWN)
		return (&data->textures.player_down);
	if (data->player_dir == LEFT)
		return (&data->textures.player_left);
	if (data->player_dir == RIGHT)
		return (&data->textures.player_right);
	return (&data->textures.player_right);
}
