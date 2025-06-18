/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/18 14:52:25 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
static t_animation	*get_tile_animation(t_data *data, char tile_type);
static t_animation	*get_current_player_anim(t_data *data);
static void			draw_tile(t_data *data, int x, int y);
static void			draw_ui(t_data *data);

/**
 * @brief The main rendering function, called on every frame by the loop hook.
 *
 * This function is the "heartbeat" of the game's visuals. It orchestrates
 * the animation timer and calls helpers to draw the map, the player, and the UI.
 *
 * @param data A pointer to the main game data struct.
 * @return int (Unused but required by MLX).
 */
int	render_frame(t_data *data)
{
	t_animation	*player_anim;
	int			x;
	int			y;

	// Clear the window to black before drawing anything else.
	mlx_clear_window(data->mlx, data->win);

	data->anim_timer = (data->anim_timer + 1) % (ANIMATION_SPEED * 100);
	if (data->anim_timer % ANIMATION_SPEED == 0)
		data->anim_frame++;
	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
			draw_tile(data, x, y);
	}
	player_anim = get_current_player_anim(data);
	if (player_anim && player_anim->frames)
		mlx_put_image_to_window(data->mlx, data->win,
			player_anim->frames[data->anim_frame % player_anim->frame_count].ptr,
			data->player_pos.x * TILE_SIZE, data->player_pos.y * TILE_SIZE);
	draw_ui(data);
	return (0);
}

/**
 * @brief A helper to draw a single tile from the map grid.
 *
 * This function now uses the modulo operator (%) to correctly loop animations
 * of any length using the global animation timer.
 */
static void	draw_tile(t_data *data, int x, int y)
{
	char		tile_type;
	t_animation	*anim;
	int			frame_to_draw;

	tile_type = data->map.grid[y][x];
	anim = get_tile_animation(data, tile_type);
	if (!anim || !anim->frames)
		return ;
	frame_to_draw = data->anim_frame % anim->frame_count;
	mlx_put_image_to_window(data->mlx, data->win,
		anim->frames[frame_to_draw].ptr, x * TILE_SIZE, y * TILE_SIZE);
}

/**
 * @brief A helper that returns a pointer to the correct animation struct
 * based on the character type from the map grid.
 */
static t_animation	*get_tile_animation(t_data *data, char tile_type)
{
	if (tile_type == '1')
		return (&data->textures.fort_wall);
	else if (tile_type == 'C')
		return (&data->textures.key);
	else if (tile_type == 'E')
		return (&data->textures.door); // Final Exit Door
	else if (tile_type == 'W')
		return (&data->textures.wall);
	// --- Add cases for your other game objects ---
	
	// --- Text Blocks ---
	else if (tile_type == 'b') // 'b' for "BABA" text
		return (&data->textures.player_txt);
	else if (tile_type == 'y')
		return (&data->textures.you_txt);
	else if (tile_type == 'd')
		return (&data->textures.door_txt);
	else if (tile_type == 'n')
		return (&data->textures.win_txt);
	else if (tile_type == 'k') // 'k' for "KEY" text
		return (&data->textures.key_txt);
	else if (tile_type == 'w')
		return (&data->textures.wall_txt);  
	else if (tile_type == 'o')
		return (&data->textures.open_txt);
	else if (tile_type == 'u') // Use 'u' for "PUSH" text
		return (&data->textures.push_txt);
	else if (tile_type == 'i')
		return (&data->textures.is_txt);

	// For '0' (empty space) and 'P' (player start), we return NULL
	// so the background shows through.
	return (NULL);
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
	return (&data->textures.player_down);
}

/**
 * @brief Draws the static UI elements like "BABA IS YOU" over the game.
 */
static void	draw_ui(t_data *data)
{
	// Example: Draw "BABA IS YOU" at a fixed position
	// You will need to find the pixel coordinates you like.
	// mlx_put_image_to_window(data->mlx, data->win, data->textures.player_txt.frames[0].ptr, 10, 10);
	// mlx_put_image_to_window(data->mlx, data->win, data->textures.is_txt.frames[0].ptr, 10 + TILE_SIZE, 10);
	// mlx_put_image_to_window(data->mlx, data->win, data->textures.you_txt.frames[0].ptr, 10 + (2 * TILE_SIZE), 10);
	(void) data;
	return ;

	// Here you would add logic to draw the key counter UI if keys are collected
}