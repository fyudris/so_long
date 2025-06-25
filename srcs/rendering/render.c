/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:37:51 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 21:14:19 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void			draw_frame_content(t_data *data);
static void			draw_map_to_buffer(t_data *data);
static void			draw_player(t_data *data);
static t_animation	*get_tile_animation(t_data *data, char tile_type);

/**
 * @brief The main rendering loop hook, responsible for timing and framerate.
 * 
 * @details This function is called on every loop by MiniLibX. It uses a
 * frame limiter to ensure the game runs at a consistent ~60 FPS, which
 * prevents high CPU usage. If enough time has passed since the last
 * frame, it calls a helper function to draw the actual frame content.
 *
 * @param data A pointer to the main game data struct.
 * @return int Always returns 0.
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
	draw_frame_content(data);
	data->last_time = current_time;
	return (0);
}

/**
 * @brief Draws all content for a single frame.
 * @details This helper function contains the actual rendering logic. It updates
 * animation timers, clears the back buffer, and draws the map and player
 * before pushing the final image to the window.
 */
static void	draw_frame_content(t_data *data)
{
	data->anim_timer++;
	if (data->anim_timer >= ANIMATION_SPEED)
	{
		data->anim_timer = 0;
		data->anim_frame++;
	}
	clear_image_buffer(&data->game_buffer, 0x000000);
	draw_map_to_buffer(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->game_buffer.ptr, 0, 0);
}

/**
 * @brief Draws all map tiles to the off-screen buffer.
 */
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
 * @brief Draws the player sprite to the off-screen buffer.
 */
static void	draw_player(t_data *data)
{
	t_animation	*player_anim;

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
		draw_sprite_to_buffer(&data->game_buffer, &player_anim->frames[0],
			(t_vector){data->player_pos.x * TILE_SIZE,
			data->player_pos.y * TILE_SIZE});
	}
}

/**
 * @brief Returns the animation struct for a given mandatory map character.
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
