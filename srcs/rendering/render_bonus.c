/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 20:00:54 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_bonus.c
 * @brief Main rendering functions for the BONUS version of so_long.
 * @details This file orchestrates the drawing of each frame by calling
 * helper functions to handle specific parts of the rendering process.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void	draw_frame_content_bonus(t_data *data);
static void	draw_map_to_buffer_bonus(t_data *data);
static void	draw_player_bonus(t_data *data);
static void	draw_ui_bonus(t_data *data);

/**
 * @brief The main rendering loop hook for the bonus version.
 */
int	render_frame(t_data *data)
{
	long	current_time;
	long	time_diff;

	current_time = get_time_in_usec();
	if (data->last_time == 0)
		data->last_time = current_time;
	time_diff = current_time - data->last_time;
	if (time_diff < FRAME_DURATION)
		return (0);
	draw_frame_content_bonus(data);
	data->last_time = current_time;
	return (0);
}

/**
 * @brief Draws all content for a single bonus frame.
 */
static void	draw_frame_content_bonus(t_data *data)
{
	data->anim_timer++;
	if (data->anim_timer >= ANIMATION_SPEED)
	{
		data->anim_timer = 0;
		data->anim_frame++;
	}
	clear_image_buffer(&data->game_buffer, 0x000000);
	draw_map_to_buffer_bonus(data);
	draw_player_bonus(data);
	mlx_put_image_to_window(data->mlx, data->win, data->game_buffer.ptr, 0,
		UI_HEIGHT);
	draw_ui_bonus(data);
}

/**
 * @brief Draws all map tiles to the off-screen buffer for the bonus version.
 */
static void	draw_map_to_buffer_bonus(t_data *data)
{
	int			x;
	int			y;
	t_animation	*anim;
	int			frame;

	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			anim = get_object_anim(data, data->map.grid[y][x]);
			if (anim && anim->frames)
			{
				frame = data->anim_frame % anim->frame_count;
				draw_sprite_to_buffer(&data->game_buffer, &anim->frames[frame],
					(t_vector){x * TILE_SIZE, y * TILE_SIZE});
			}
		}
	}
}

/**
 * @brief Draws the player with complex animation for the bonus version.
 */
static void	draw_player_bonus(t_data *data)
{
	t_animation	*player_anim;
	int			frame_index;

	if (data->player_dir == UP)
		player_anim = &data->textures.player_up;
	else if (data->player_dir == DOWN)
		player_anim = &data->textures.player_down;
	else if (data->player_dir == LEFT)
		player_anim = &data->textures.player_left;
	else
		player_anim = &data->textures.player_right;
	if (player_anim && player_anim->frames)
	{
		frame_index = 0;
		if (data->is_moving == true)
			frame_index = data->anim_frame % player_anim->frame_count;
		draw_sprite_to_buffer(&data->game_buffer,
			&player_anim->frames[frame_index],
			(t_vector){data->player_pos.x * TILE_SIZE,
			data->player_pos.y * TILE_SIZE});
	}
}

/**
 * @brief Draws the graphical UI panel by calling helper functions.
 */
static void	draw_ui_bonus(t_data *data)
{
	draw_ui_left(data);
	draw_ui_right(data);
}
