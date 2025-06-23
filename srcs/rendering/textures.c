/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:55:53 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/23 12:55:16 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief A helper that now unpacks AND upscales a single frame.
 */
static void	process_one_frame(t_data *data, t_img *final_img, t_img *sheet,
		t_vector pos)
{
	t_img	small_sprite;

	// 1. Create temporary small canvas for the original sprite
	small_sprite.ptr = mlx_new_image(data->mlx,
			ORIGINAL_TILE_SIZE, ORIGINAL_TILE_SIZE);
	small_sprite.width = ORIGINAL_TILE_SIZE;
	small_sprite.height = ORIGINAL_TILE_SIZE;
	small_sprite.addr = mlx_get_data_addr(small_sprite.ptr, &small_sprite.bpp,
			&small_sprite.line_len, &small_sprite.endian);

	// 2. Unpack the sprite from the sheet onto the small canvas
	unpack_sprite(&small_sprite, sheet, pos);

	// 3. Create the final, larger canvas
	final_img->ptr = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	final_img->width = TILE_SIZE;
	final_img->height = TILE_SIZE;
	final_img->addr = mlx_get_data_addr(final_img->ptr, &final_img->bpp,
			&final_img->line_len, &final_img->endian);

	// 4. Upscale the small sprite onto the final canvas
	upscale_sprite(final_img, &small_sprite);

	// 5. Destroy the temporary small sprite canvas
	mlx_destroy_image(data->mlx, small_sprite.ptr);
}


/**
 * @brief The main function for loading any animation sequence from a spritesheet.
 *
 * This function is now flexible. It can load an animation of any length,
 * starting at any (x,y) pixel coordinate on the sheet, and can read the
 * frames either horizontally or vertically.
 *
 * Imagine your spritesheet is a grid. Let's assume your TILE_SIZE is 24.
 * (x=0,y=0)   (x=24,y=0)  (x=48,y=0)
 * +-----------+-----------+-----------+
 * |           |           |           |
 * | Sprite A  | Sprite B  | Sprite C  |
 * |           |           |           |
 * +-----------+-----------+-----------+
 * |           |           |           |
 * | Sprite D  | Sprite E  | Sprite F  |
 * |           |           |           |
 * +-----------+-----------+-----------+
 * (x=0,y=24)
 *
 * @param data The main game data struct.
 * @param anim A pointer to the t_animation struct to populate.
 * @param path The path to the source .xpm spritesheet.
 * @param frame_count The number of frames in this specific animation.
 * @param start_pos The top-left (x,y) pixel coordinate of the FIRST frame.
 * @param orientation The layout of the frames (HORIZONTAL or VERTICAL).
 */
static void	load_animation(t_data *data, t_animation *anim, char *path,
		int frame_count, t_vector start_pos)
{
	t_img	sheet;
	int		i;

	anim->frame_count = frame_count;
	anim->frames = malloc(sizeof(t_img) * frame_count);
	if (!anim->frames)
		ft_print_error("Malloc failed for animation.");
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, path,
			&sheet.width, &sheet.height);
	if (!sheet.ptr)
	{
		ft_printf("Failed to load spritesheet: %s", path);
		cleanup_and_exit(data, 1);
	}
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);

	i = -1;
	while (++i < frame_count)
	{
		// This now correctly assumes a vertical strip starting at start_pos
		process_one_frame(data, &anim->frames[i], &sheet,
			(t_vector){start_pos.x, start_pos.y + (i * ORIGINAL_TILE_SIZE)});
	}
	mlx_destroy_image(data->mlx, sheet.ptr);
}

/**
 * @brief A specialized function to load Baba's complex 12-frame animations.
 *
 * This function iterates through the 3 rows and 4 columns that make up
 * a single walking direction for Baba.
 *
 * @param start_col The starting column index for this animation (e.g., 0 for right, 4 for left).
 */
static void	load_baba_animation(t_data *data, t_animation *anim,
		char *path, int start_col)
{
	t_img	sheet;
	int		pose;
	int		row;

	anim->frame_count = BABA_WALK_FRAMES;
	anim->frames = malloc(sizeof(t_img) * BABA_WALK_FRAMES);
	if (!anim->frames)
		ft_print_error("Malloc failed for Baba animation.");
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, path,
		&sheet.width, &sheet.height);
	if (!sheet.ptr)
	{
		ft_print_error("Failed to load Baba spritesheet.");
		cleanup_and_exit(data, 1);
	}
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);
	row = -1;
	while (++row < 3)
	{
		pose = -1;
		while (++pose < 4)
		{
			process_one_frame(data, &anim->frames[(row * 4) + pose], &sheet,
				(t_vector){(start_col + pose) * ORIGINAL_TILE_SIZE,
				row * ORIGINAL_TILE_SIZE});
		}
	}
	mlx_destroy_image(data->mlx, sheet.ptr);
}

/**
 * @brief Manually define the coordinates for each digit on the spritesheet.
 * This function acts as a hardcoded map for our irregular font sheet.
 */
static void	init_digit_coords(t_data *data)
{
	// You must find these exact coordinates using GIMP. These are examples.
	// The index corresponds to the digit (e.g., index 0 is for digit '0').
	data->textures.digit_coords[0] = (t_vector){250, 225}; // Coords for '0'
	data->textures.digit_coords[1] = (t_vector){300, 225}; // Coords for '1'
	data->textures.digit_coords[2] = (t_vector){0, 300};   // Coords for '2'
	data->textures.digit_coords[3] = (t_vector){50, 300};  // Coords for '3'
	data->textures.digit_coords[4] = (t_vector){100, 300};  // Coords for '4'
	data->textures.digit_coords[5] = (t_vector){150, 300};  // Coords for '5'
	data->textures.digit_coords[6] = (t_vector){200, 300}; // Coords for '6'
	data->textures.digit_coords[7] = (t_vector){250, 300}; // Coords for '7'
	data->textures.digit_coords[8] = (t_vector){300, 300}; // Coords for '8'
	data->textures.digit_coords[9] = (t_vector){0, 375};   // Coords for '9'
}

/**
 * @brief The main public function to load all visual assets for the game.
 * It calls specialized helpers for different types of spritesheets.
 *
 * Column Index		Pixel Start (x)		Content
 * 0				0					BABA Text
 * 1 - 4			25, 50, 75, 100		Walk Right Animation (4 frames)
 * 5 - 8			125, 150, ...		Walk Left Animation (4 frames)
 * 9 - 12			225, ...			Walk Up Animation (4 frames)
 * 13 - 16			325, ...			Walk Down Animation (4 frames)
 *
 * Indexing
 * Column		Coordinate
 * 0			x = 0
 * 1			x = 25
 * 2			x = 50
 * 3			x = 75
 * 4			x = 100
 *
 */
void	load_all_textures(t_data *data)
{
	int	i;

	load_baba_animation(data, &data->textures.player_right, BABA_PATH, 1);
	load_baba_animation(data, &data->textures.player_up, BABA_PATH, 5);
	load_baba_animation(data, &data->textures.player_left, BABA_PATH, 9);
	load_baba_animation(data, &data->textures.player_down, BABA_PATH, 13);
	load_animation(data, &data->textures.player_txt, BABA_PATH, 3,
		(t_vector){0,0});
	load_animation(data, &data->textures.wall, WALL_PATH, 3,
		(t_vector){50,0});
	load_animation(data, &data->textures.wall_txt, WALL_PATH, 3,
		(t_vector){25,0});
	load_animation(data, &data->textures.fort_wall, FORT_PATH, 3,
		(t_vector){50,0});
	load_animation(data, &data->textures.key, KEY_PATH, 3,
		(t_vector){100,0});
	load_animation(data, &data->textures.key_txt, KEY_PATH, 3,
		(t_vector){75,0});
	load_animation(data, &data->textures.door, DOOR_PATH, 3,
		(t_vector){100,0});
	load_animation(data, &data->textures.door_txt, DOOR_PATH, 3,
		(t_vector){75, 0});
	load_animation(data, &data->textures.rock, ROCK_PATH, 3,
		(t_vector){100,0});
	load_animation(data, &data->textures.rock_txt, ROCK_PATH, 3,
		(t_vector){75, 0});
	load_animation(data, &data->textures.you_txt, YOU_PATH, 3,
		(t_vector){50,0});
	load_animation(data, &data->textures.is_txt, IS_PATH, 3,
		(t_vector){0,0});
	load_animation(data, &data->textures.open_txt, OPEN_PATH, 3,
		(t_vector){50,0});
	load_animation(data, &data->textures.push_txt, PUSH_PATH, 3,
		(t_vector){50,0});
	load_animation(data, &data->textures.win_txt, WIN_PATH, 3,
		(t_vector){25,0});
	init_digit_coords(data);
	i = 0;
	while (i < 10)
	{
		load_animation(data, &data->textures.ui_digits[i], FONT_PATH,
			3, data->textures.digit_coords[i]);
		i++;
	}
	load_animation(data, &data->textures.ui_key_icon, KEY_PATH,
		3, (t_vector){100, 0});
	load_animation(data, &data->textures.ui_move_icon, MOVE_PATH,
		3, (t_vector){50, 0});
	load_animation(data, &data->textures.ui_x_icon, FONT_PATH,
		3, (t_vector){100, 225});

}
