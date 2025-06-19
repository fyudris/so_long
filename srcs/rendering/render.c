/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:33 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/19 14:58:31 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"
static t_animation	*get_tile_animation(t_data *data, char tile_type);
static t_animation	*get_current_player_anim(t_data *data);
static void			draw_tile(t_data *data, int x, int y);
static void			draw_ui(t_data *data);
static int	player_anim_frame(t_data *data, t_animation *player_anim);

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
	int			x;
	int			y;

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
	// 3. Draw all the map tiles by looping through the grid.
	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
			draw_tile(data, x, y);
	}
	// 4. Draw the player on top of the map.
	player_anim = get_current_player_anim(data);
	if (player_anim && player_anim->frames)
		mlx_put_image_to_window(data->mlx, data->win,
			player_anim->frames[player_anim_frame(data, player_anim)].ptr,
			data->player_pos.x * TILE_SIZE, data->player_pos.y * TILE_SIZE);
	// 5. Draw the static UI text on top of everything.
	draw_ui(data);
	return (0);
}


/**
 * @brief A helper to draw a single tile from the map grid.
 *
 * It looks up the correct animation for the tile type and uses the global
 * animation frame number to draw the correct frame for that animation.
 */
static void	draw_tile(t_data *data, int x, int y)
{
	char		tile_type;
	t_animation	*anim;
	int			frame_to_draw;

	tile_type = data->map.grid[y][x];
	anim = get_tile_animation(data, tile_type);
	// If anim is NULL (for '0' or 'P'), we draw nothing.
	if (!anim || !anim->frames)
		return ;
	// Use the modulo operator to loop the animation correctly.
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
 * @brief Draws the static UI elements like the "Rule Box".
 * The rule box text is part of the map grid, so this function is
 * for elements that are NOT part of the grid, like a key counter.
 */
static void	draw_ui(t_data *data)
{
	char	*str_moves;

	// This is now only for UI elements NOT on the map grid.
	// The "BABA IS YOU" text in your level design is part of the map
	// and is already drawn by the draw_tile loop.

	// Example: Draw the move count in the top-left corner.
	// This is a bonus feature from the so_long.pdf subject guide.
	str_moves = ft_itoa(data->move_count);
	mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, "MOVES:");
	mlx_string_put(data->mlx, data->win, 80, 20, 0xFFFFFF, str_moves);
	free(str_moves);

	// Here you would add logic to draw a Key icon if data->player_has_key is true.
}