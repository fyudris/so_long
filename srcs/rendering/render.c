/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 14:20:36 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
static t_animation	*get_tile_animation(t_data *data, char tile_type);
static t_animation	*get_current_player_anim(t_data *data);
// static void			draw_tile(t_data *data, int x, int y);
static void			draw_ui(t_data *data);
static int	player_anim_frame(t_data *data, t_animation *player_anim);
static void draw_map_to_buffer(t_data *data);
static void	draw_ui(t_data *data);

/**
 * @brief The main rendering function, called on every frame by the loop hook.
 *
 * This function is the "heartbeat" of the game's visuals. It clears the
 * screen and redraws every animated element in the correct order.
 *
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	render_frame(t_data *data)
{
	t_animation	*player_anim;
	int			player_frame_index;

	// 1. Update animation timers
	data->anim_timer++;
	if (data->anim_timer >= ANIMATION_SPEED)
	{
		data->anim_timer = 0;
		data->anim_frame++;
	}

	// 2. Clear the BACK BUFFER to black to prevent after-images.
	clear_image_buffer(&data->game_buffer, 0x000000);

	// 3. Draw the entire map to the off-screen buffer.
	draw_map_to_buffer(data);

	// 4. Draw the player ON TOP of the map buffer.
	player_anim = get_current_player_anim(data);
	if (player_anim && player_anim->frames)
	{
		player_frame_index = player_anim_frame(data, player_anim);
		draw_sprite_to_buffer(&data->game_buffer,
			&player_anim->frames[player_frame_index],
			(t_vector){data->player_pos.x * TILE_SIZE, data->player_pos.y * TILE_SIZE});
	}

	// --- Final Window Drawing (in correct order) ---

	// 5. Push the ENTIRE completed game buffer to the window in ONE call.
	mlx_put_image_to_window(data->mlx, data->win, data->game_buffer.ptr, 0, UI_HEIGHT);

	// 6. NOW, draw the UI elements directly on top of the window.
	draw_ui(data);

	return (0);
}


/**
 * @brief Draws the entire map grid with a vertical offset for the UI bar.
 */
static void draw_map_to_buffer(t_data *data)
{
	int			x;
	int			y;
	char		tile_type;
	t_animation	*anim;
	int			frame;
	t_img		*tile_img;

	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			// We need a black background first. Let's handle this in render_frame.

			tile_type = data->map.grid[y][x];
			anim = get_tile_animation(data, tile_type);
			if (anim && anim->frames)
			{
				frame = data->anim_frame % anim->frame_count;
				tile_img = &anim->frames[frame];
				// Use your existing function to draw the tile sprite to the buffer
				draw_sprite_to_buffer(&data->game_buffer, tile_img,
					(t_vector){x * TILE_SIZE, y * TILE_SIZE});
			}
		}
	}
}

/**
 * @brief Draws a number to the screen using loaded digit sprites.
 * This function handles converting an integer to a string and drawing
 * the corresponding sprite for each digit.
 */
static void	draw_number(t_data *data, int n, t_vector pos)
{
	char	*str_num;
	int		i;
	int		digit;

	// Special case for drawing the number 0
	if (n == 0)
	{
		if (data->textures.ui_digits[0].frames)
			mlx_put_image_to_window(data->mlx, data->win,
				data->textures.ui_digits[0].frames[0].ptr, pos.x, pos.y);
		return ;
	}
	str_num = ft_itoa(n);
	if (!str_num)
		return ;
	i = 0;
	while (str_num[i])
	{
		digit = str_num[i] - '0';
		// Safety check before drawing
		if (data->textures.ui_digits[digit].frames)
			mlx_put_image_to_window(data->mlx, data->win,
				data->textures.ui_digits[digit].frames[0].ptr,
				pos.x + (i * TILE_SIZE), pos.y);
		i++;
	}
	free(str_num);
}




// /**
//  * @brief A helper to draw a single tile from the map grid.
//  *
//  * It looks up the correct animation for the tile type and uses the global
//  * animation frame number to draw the correct frame for that animation.
//  */
// static void	draw_tile(t_data *data, int x, int y)
// {
// 	char		tile_type;
// 	t_animation	*anim;
// 	int			frame_to_draw;

// 	tile_type = data->map.grid[y][x];
// 	anim = get_tile_animation(data, tile_type);
// 	// If anim is NULL (for '0' or 'P'), we draw nothing.
// 	if (!anim || !anim->frames)
// 		return ;
// 	// Use the modulo operator to loop the animation correctly.
// 	frame_to_draw = data->anim_frame % anim->frame_count;
// 	mlx_put_image_to_window(data->mlx, data->win,
// 		anim->frames[frame_to_draw].ptr, x * TILE_SIZE, y * TILE_SIZE);
// }

/**
 * @brief A helper that returns a pointer to the correct animation struct
 * based on the character type from the map grid.
 */
static t_animation	*get_tile_animation(t_data *data, char tile_type)
{
	if (tile_type == '1')
		return (&data->textures.fort_wall);
	if (tile_type == 'C')
		return (&data->textures.key);
	if (tile_type == 'c')
		return (&data->textures.key_txt);
	if (tile_type == 'E')
		return (&data->textures.door);
	if (tile_type == 'e')
		return (&data->textures.door_txt);
	if (tile_type == 'W')
		return (&data->textures.wall);
	if (tile_type == 'w')
		return (&data->textures.wall_txt);
	if (tile_type == 'R')
		return (&data->textures.rock);
	if (tile_type == 'r')
		return (&data->textures.rock_txt);
	// --- Add cases for your other game objects ---

	// --- Text Blocks ---
	if (tile_type == 'p') // 'b' for "BABA" text
		return (&data->textures.player_txt);
	if (tile_type == 'y')
		return (&data->textures.you_txt);
	if (tile_type == 'n')
		return (&data->textures.win_txt);
	if (tile_type == 'o')
		return (&data->textures.open_txt);
	if (tile_type == 'u') // Use 'u' for "PUSH" text
		return (&data->textures.push_txt);
	if (tile_type == 'i')
		return (&data->textures.is_txt);
	// For '0' (empty space) and 'P' (player start), we return NULL
	// so the background shows through.
	return (NULL);
}

/**
 * @brief Selects the correct player animation sequence and frame.
 */
static int	player_anim_frame(t_data *data, t_animation *player_anim)
{
	if (data->is_moving == false)
		return (0); // If idle, always show the first frame.
	// If moving, use the global anim_frame but loop it with the player's
	// specific frame count (which is 12).
	return (data->anim_frame % player_anim->frame_count);
}

/**
 * @brief Selects the correct player animation sequence based on direction.
 */
static t_animation	*get_current_player_anim(t_data *data)
{
	// The anim_frame reset is now correctly handled only in handle_keyrelease
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

/**
 * @brief Draws the entire UI panel at the top of the window.
 * This final version uses icons for both the move and key counters and
 * handles alignment correctly.
 */
static void	draw_ui(t_data *data)
{
	char	*key_str;
	int		key_counter_width;
	int		win_width;

	// --- Draw Move Counter on the LEFT ---
	// Consists of: [MOVE icon] [x icon] [number]
	if (data->textures.ui_move_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_move_icon.frames[0].ptr, 20, 10);
	if (data->textures.ui_x_icon.frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_x_icon.frames[0].ptr, 20 + TILE_SIZE, 10);
	draw_number(data, data->move_count,
		(t_vector){20 + (2 * TILE_SIZE), 10});

	// --- Draw Key Counter on the RIGHT ---
	key_str = ft_itoa(data->keys_collected);
	if (!key_str)
		return ;
	// Calculate total width: (key icon + x icon + num of digits)
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

