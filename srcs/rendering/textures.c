/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:27:31 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:28:56 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

// Forward declarations for static helpers
static void	process_one_frame(t_data *data, t_img *final_img,
				t_img *sheet, t_vector pos);
static void	load_animation(t_data *data, t_animation *anim,
				char *path, t_vector start_pos);
static void	load_player_anims_mandatory(t_data *data);

/**
 * @brief Main texture loader for the MANDATORY part.
 */
void	load_all_textures(t_data *data)
{
	load_player_anims_mandatory(data);
	load_animation(data, &data->textures.fort_wall, FORT_PATH,
		(t_vector){50, 0});
	load_animation(data, &data->textures.key, KEY_PATH, (t_vector){100, 0});
	load_animation(data, &data->textures.door, DOOR_PATH, (t_vector){100, 0});
}

/**
 * @brief A simplified helper to load the four directional player sprites.
 * For mandatory, we assume each direction is a single, static frame.
 */
static void	load_player_anims_mandatory(t_data *data)
{
	load_animation(data, &data->textures.player_right, BABA_PATH,
		(t_vector){25, 0});
	load_animation(data, &data->textures.player_up, BABA_PATH,
		(t_vector){125, 0});
	load_animation(data, &data->textures.player_left, BABA_PATH,
		(t_vector){225, 0});
	load_animation(data, &data->textures.player_down, BABA_PATH,
		(t_vector){325, 0});
}

/**
 * @brief Generic loader for a SINGLE frame animation from a specific coordinate.
 */
static void	load_animation(t_data *data, t_animation *anim,
			char *path, t_vector start_pos)
{
	t_img	sheet;

	anim->frame_count = 1;
	anim->frames = malloc(sizeof(t_img));
	if (!anim->frames)
		cleanup_and_exit(data, 1);
	sheet.ptr = mlx_xpm_file_to_image(data->mlx, path,
			&sheet.width, &sheet.height);
	if (!sheet.ptr)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		cleanup_and_exit(data, 1);
	}
	sheet.addr = mlx_get_data_addr(sheet.ptr, &sheet.bpp,
			&sheet.line_len, &sheet.endian);
	process_one_frame(data, &anim->frames[0], &sheet, start_pos);
	mlx_destroy_image(data->mlx, sheet.ptr);
}

/**
 * @brief Helper to unpack and upscale a single sprite frame.
 */
static void	process_one_frame(t_data *data, t_img *final_img,
			t_img *sheet, t_vector pos)
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
