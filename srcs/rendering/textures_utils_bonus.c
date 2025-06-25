/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:46:48 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:29:04 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file textures_utils_bonus.c
 * @brief Low-level utility functions for loading textures (Bonus).
 * @details This file contains the core logic for processing spritesheets,
 * including loading multi-frame animations. It is separated to keep the main
 * texture loading file compliant with the Norm.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

// Forward declaration for the new static helper function
static void	process_baba_frames(t_data *data, t_animation *anim,
				t_img *sheet, int start_col);

/**
 * @brief A helper that unpacks AND upscales a single frame from a spritesheet.
 */
void	process_one_frame(t_data *data, t_img *final_img, t_img *sheet,
		t_vector pos)
{
	t_img	small_sprite;

	small_sprite.ptr = mlx_new_image(data->mlx,
			ORIGINAL_TILE_SIZE, ORIGINAL_TILE_SIZE);
	if (!small_sprite.ptr)
		cleanup_and_exit(data, 1);
	small_sprite.width = ORIGINAL_TILE_SIZE;
	small_sprite.height = ORIGINAL_TILE_SIZE;
	small_sprite.addr = mlx_get_data_addr(small_sprite.ptr, &small_sprite.bpp,
			&small_sprite.line_len, &small_sprite.endian);
	unpack_sprite(&small_sprite, sheet, pos);
	final_img->ptr = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	if (!final_img->ptr)
		cleanup_and_exit(data, 1);
	final_img->width = TILE_SIZE;
	final_img->height = TILE_SIZE;
	final_img->addr = mlx_get_data_addr(final_img->ptr, &final_img->bpp,
			&final_img->line_len, &final_img->endian);
	upscale_sprite(final_img, &small_sprite);
	mlx_destroy_image(data->mlx, small_sprite.ptr);
}

/**
 * @brief Loads any animation sequence from a spritesheet.
 * @details This function is now compliant with the 4-argument Norm limit by
 * accepting a t_anim_info struct containing the loading parameters.
 *
 * @param data The main game data struct.
 * @param anim A pointer to the t_animation struct to populate.
 * @param info A struct containing the path, frame_count, and start_pos.
 */
void	load_animation(t_data *data, t_animation *anim, t_anim_info info)
{
	t_img	sheet;
	int		i;

	anim->frame_count = info.frame_count;
	anim->frames = malloc(sizeof(t_img) * info.frame_count);
	if (!anim->frames)
		cleanup_and_exit(data, 1);
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, info.path,
			&sheet.width, &sheet.height);
	if (!sheet.ptr)
	{
		ft_printf("Error\nFailed to load spritesheet: %s\n", info.path);
		cleanup_and_exit(data, 1);
	}
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);
	i = -1;
	while (++i < info.frame_count)
	{
		process_one_frame(data, &anim->frames[i], &sheet,
			(t_vector){info.start_pos.x,
			info.start_pos.y + (i * ORIGINAL_TILE_SIZE)});
	}
	mlx_destroy_image(data->mlx, sheet.ptr);
}

/**
 * @brief Iterates through the Baba spritesheet to process all 12 frames.
 * @details This helper function contains the nested loop to extract each
 * frame of a single walking animation for Baba.
 *
 * @param data A pointer to the main data struct.
 * @param anim The animation struct to populate.
 * @param sheet The loaded spritesheet image.
 * @param start_col The starting column index for the animation sequence.
 */
static void	process_baba_frames(t_data *data, t_animation *anim,
		t_img *sheet, int start_col)
{
	int	pose;
	int	row;

	row = -1;
	while (++row < 3)
	{
		pose = -1;
		while (++pose < 4)
			process_one_frame(data, &anim->frames[(row * 4) + pose], sheet,
				(t_vector){(start_col + pose) * ORIGINAL_TILE_SIZE,
				row * ORIGINAL_TILE_SIZE});
	}
}

/**
 * @brief A specialized function to load Baba's complex 12-frame animations.
 * @details This function now handles the initial setup (malloc, loading the
 * sheet) and then calls a helper function to process the frames, keeping it
 * compliant with the 25-line limit.
 */
void	load_baba_animation(t_data *data, t_animation *anim,
		char *path, int start_col)
{
	t_img	sheet;

	anim->frame_count = BABA_WALK_FRAMES;
	anim->frames = malloc(sizeof(t_img) * BABA_WALK_FRAMES);
	if (!anim->frames)
		cleanup_and_exit(data, 1);
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, path,
			&sheet.width, &sheet.height);
	if (!sheet.ptr)
	{
		ft_printf("Error\nFailed to load Baba spritesheet: %s\n", path);
		cleanup_and_exit(data, 1);
	}
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);
	process_baba_frames(data, anim, &sheet, start_col);
	mlx_destroy_image(data->mlx, sheet.ptr);
}
