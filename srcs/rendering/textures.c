/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:55:53 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 19:43:09 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief copies a rectangular area of pixels from a source to a destination.
 * 
 * This function iterates through a defined rectangle on the source spritesheet
 * and copies each pixel to the destination image, effectively "unpacking" a
 * single sprite.
 * 
 * @param dest The destination image (must be pre-allocated)
 * @param src The source spritesheet
 * @param pos The top-left (x,y) coordinate of the sprite on the source sheet.
 */
static void	unpack_sprite(t_img *dest, t_img *src, t_vector pos)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < dest->height)
	{
		x = 0;
		while (x < dest->width)
		{
			// Get the color from the source sheet at an offset
			color = get_pixel_from_img(src, pos.x + x, pos.y + y);
			// Put that color into the destination image at the correct spot
			put_pixel_to_img(dest, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Loads a sprite, upscales it, and stores it.
 *
 * This function now performs a multi-step process:
 * 1. Loads the entire source spritesheet.
 * 2. Unpacks the desired small sprite into a temporary image.
 * 3. Creates a new, larger destination image.
 * 4. Calls upscale_sprite to scale the small sprite onto the large one.
 * 5. Frees the temporary small sprite and the original spritesheet.
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
 *
 * @param data The main game data struct.
 * @param dest_img Pointer to the t_img where the FINAL SCALED sprite is stored.
 * @param sheet_path The path to the source .xpm spritesheet.
 * @param pos The top-left (x,y) coordinate of the sprite on the sheet.
 * 
 * @param data The main game data struct.
 * @param dest_img A pointer to the t_img struct where the final sprite will
 * be stored.
 * @param sheet_path The path tot he source .xmp spritesheet
 * @param pos The top-left (x,y) coordinate of the sprite on the sheet
 */
static void	load_one_texture(t_data *data, t_img *dest_img, char *sheet_path,
		t_vector pos)
{
	t_img	sheet;
	t_img	small_sprite; // A temporary image to hold the original small sprite

	// Load the original spritesheet
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, sheet_path,
			&sheet.width, &sheet.height);
	if (!sheet.ptr)
		ft_print_error("Failed to load spritesheet.");
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);

	//Create a temporary small sprite canvas and unpack
	small_sprite.ptr = mlx_new_image(data->mlx, 24, 24); // Your original TILE_SIZE
	small_sprite.addr = mlx_get_data_addr(small_sprite.ptr, &small_sprite.bpp,
			&small_sprite.line_len, &small_sprite.endian);
	small_sprite.width = 24;
	small_sprite.height = 24;
	unpack_sprite(&small_sprite, &sheet, pos);

	//Create the final, larger destination image
	dest_img->ptr = mlx_new_image(data->mlx, 24 * SCALE_FACTOR, 24 * SCALE_FACTOR);
	dest_img->addr = mlx_get_data_addr(dest_img->ptr, &dest_img->bpp,
			&dest_img->line_len, &dest_img->endian);
	dest_img->width = 24 * SCALE_FACTOR;
	dest_img->height = 24 * SCALE_FACTOR;

	//Scale the small sprite onto the large one
	upscale_sprite(dest_img, &small_sprite);

	//Cleanup
	mlx_destroy_image(data->mlx, sheet.ptr);
	mlx_destroy_image(data->mlx, small_sprite.ptr);
}

/**
 * @brief Loads all game textures by unpacking them from their spritesheets.
 *
 * This function calls the load_one_texture helper for every single sprite
 * needed in the game, providing the correct path and coordinates on the
 * spritesheet for each one.
 *
 * @param data A pointer to the main game data struct.
 */
void	load_all_textures(t_data *data)
{
	// NOTE: You will need to open your .xpm files in an image editor
	// to find the exact top-left pixel coordinates for each sprite.
	// The values here are examples.

	// Load just the top-left sprite from Baba.xpm to be our static player image.
	load_one_texture(data, &data->textures.player,
		"./assets/characters/Baba.xpm", (t_vector){24, 0});

	// // Load all your other static textures as planned.
	// // You will need to find the correct coordinates for these.
	load_one_texture(data, &data->textures.fort_wall,
		"./assets/tiles/Fort.xpm", (t_vector){0, 0});
	// load_one_texture(data, &data->textures.wall_obj,
	// 	"assets/tiles/Wall.xpm", (t_vector){0, 0});
	// load_one_texture(data, &data->textures.key_item,
	// 	"assets/statics/Key.xpm", (t_vector){0, 0});
	// load_one_texture(data, &data->textures.exit_door,
	// 	"assets/statics/Door.xpm", (t_vector){96, 0});
	// load_one_texture(data, &data->textures.is_txt,
	// 	"assets/texts/Is-Text.xpm", (t_vector){0, 0});
}
