/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/20 12:33:28 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
static t_animation	*get_tile_animation(t_data *data, char tile_type);
static t_animation	*get_current_player_anim(t_data *data);
// static void			draw_tile(t_data *data, int x, int y);
static void			draw_ui(t_data *data);
static int	player_anim_frame(t_data *data, t_animation *player_anim);
static void	draw_map(t_data *data);
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
	// int			x;
	// int			y;

	// 1. Clear the entire window to black to prevent "smearing".
	mlx_clear_window(data->mlx, data->win);
	// 2. Update the global animation timer.
	data->anim_timer++;
	if (data->anim_timer >= ANIMATION_SPEED)
	{
		data->anim_timer = 0;
		// This frame number will be used by ALL passively animated objects.
		data->anim_frame++;
	}
	draw_map(data);
	// 4. Draw the player on top of the map with offset
	player_anim = get_current_player_anim(data);
	if (player_anim && player_anim->frames)
		mlx_put_image_to_window(data->mlx, data->win,
			player_anim->frames[player_anim_frame(data, player_anim)].ptr,
			data->player_pos.x * TILE_SIZE,
			(data->player_pos.y * TILE_SIZE) + UI_HEIGHT); // <-- ADD OFFSET

	// Draw the UI on top
	draw_ui(data);
	return (0);
}


/**
 * @brief Draws the entire map grid with a vertical offset for the UI bar.
 */
static void	draw_map(t_data *data)
{
	int	x;
	int	y;
	char	tile_type;
	t_animation	*anim;
	int	frame;

	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			tile_type = data->map.grid[y][x];
			anim = get_tile_animation(data, tile_type);
			if (anim && anim->frames)
			{
				frame = data->anim_frame % anim->frame_count;
				mlx_put_image_to_window(data->mlx, data->win,
					anim->frames[frame].ptr,
					x * TILE_SIZE,
					(y * TILE_SIZE) + UI_HEIGHT); // <-- ADD OFFSET
			}
		}
	}
}

/**
 * @brief Draws a number to the screen using loaded digit sprites.
 * It converts an integer to a string and draws the sprite for each digit.
 */
void	draw_number(t_data *data, int n, t_vector pos)
{
	char	*str;
	int		i;
	int		digit;

	if (n == 0)
	{
		// Draw the '0' sprite directly if the number is zero
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_digits[0].frames[0].ptr, pos.x, pos.y);
		return ;
	}
	str = ft_itoa(n);
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		digit = str[i] - '0';
		// Draw the corresponding digit sprite, moving horizontally for each new digit
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_digits[digit].frames[0].ptr,
			pos.x + (i * TILE_SIZE), pos.y);
		i++;
	}
	free(str);
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
 * @brief Draws the entire UI panel at the top of the window with correct alignment.
 */
static void	draw_ui(t_data *data)
{
	char	*move_str;
	char	*key_str;
	int		key_counter_width;
	int		win_width;

	// --- Draw Move Counter on the LEFT ---
	mlx_string_put(data->mlx, data->win, 20, (UI_HEIGHT / 2) + 8,
		0xFFFFFF, "MOVES:");
	move_str = ft_itoa(data->move_count);
	if (move_str)
	{
		mlx_string_put(data->mlx, data->win, 90, (UI_HEIGHT / 2) + 8,
			0xFFFFFF, move_str);
		free(move_str); // Free the string after use
	}

	// --- Draw Key Counter on the RIGHT ---
	key_str = ft_itoa(data->keys_collected);
	if (!key_str)
		return ; // Protect against malloc failure
	key_counter_width = (TILE_SIZE * 2) + (ft_strlen(key_str) * TILE_SIZE);
	win_width = data->map.size.x * TILE_SIZE;
	mlx_put_image_to_window(data->mlx, data->win,
		data->textures.ui_key_icon.frames[0].ptr,
		win_width - key_counter_width - 20, 10);
	mlx_put_image_to_window(data->mlx, data->win,
		data->textures.ui_x_icon.frames[0].ptr,
		win_width - key_counter_width - 20 + TILE_SIZE, 10);
	draw_number(data, data->keys_collected,
		(t_vector){win_width - key_counter_width - 20 + (2 * TILE_SIZE), 10});
	free(key_str); // Free the string after use
}
