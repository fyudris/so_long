/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:55:53 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:53:48 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file textures_bonus.c
 * @brief High-level texture loading functions for the BONUS version.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void	load_game_objects(t_data *data);
static void	load_text_blocks(t_data *data);
static void	load_ui_elements(t_data *data);

/**
 * @brief The main public function to load all visual assets for the game.
 */
void	load_all_textures(t_data *data)
{
	load_baba_animation(data, &data->textures.player_right, BABA_PATH, 1);
	load_baba_animation(data, &data->textures.player_up, BABA_PATH, 5);
	load_baba_animation(data, &data->textures.player_left, BABA_PATH, 9);
	load_baba_animation(data, &data->textures.player_down, BABA_PATH, 13);
	load_game_objects(data);
	load_text_blocks(data);
	load_ui_elements(data);
}

/**
 * @brief Loads all interactive game object and wall textures.
 */
static void	load_game_objects(t_data *data)
{
	load_animation(data, &data->textures.wall, (t_anim_info){WALL_PATH,
		3, (t_vector){50, 0}});
	load_animation(data, &data->textures.fort_wall, (t_anim_info){FORT_PATH,
		3, (t_vector){50, 0}});
	load_animation(data, &data->textures.key, (t_anim_info){KEY_PATH,
		3, (t_vector){100, 0}});
	load_animation(data, &data->textures.door, (t_anim_info){DOOR_PATH,
		3, (t_vector){100, 0}});
	load_animation(data, &data->textures.rock, (t_anim_info){ROCK_PATH,
		3, (t_vector){100, 0}});
}

/**
 * @brief Loads all "Baba Is You" text block textures.
 */
static void	load_text_blocks(t_data *data)
{
	load_animation(data, &data->textures.player_txt, (t_anim_info){BABA_PATH,
		3, (t_vector){0, 0}});
	load_animation(data, &data->textures.wall_txt, (t_anim_info){WALL_PATH,
		3, (t_vector){25, 0}});
	load_animation(data, &data->textures.key_txt, (t_anim_info){KEY_PATH,
		3, (t_vector){75, 0}});
	load_animation(data, &data->textures.door_txt, (t_anim_info){DOOR_PATH,
		3, (t_vector){75, 0}});
	load_animation(data, &data->textures.rock_txt, (t_anim_info){ROCK_PATH,
		3, (t_vector){75, 0}});
	load_animation(data, &data->textures.you_txt, (t_anim_info){YOU_PATH,
		3, (t_vector){50, 0}});
	load_animation(data, &data->textures.is_txt, (t_anim_info){IS_PATH,
		3, (t_vector){0, 0}});
	load_animation(data, &data->textures.open_txt, (t_anim_info){OPEN_PATH,
		3, (t_vector){50, 0}});
	load_animation(data, &data->textures.push_txt, (t_anim_info){PUSH_PATH,
		3, (t_vector){0, 0}});
	load_animation(data, &data->textures.win_txt, (t_anim_info){WIN_PATH,
		3, (t_vector){25, 0}});
}

/**
 * @brief Manually defines coordinates for each digit on the font spritesheet.
 */
static void	init_digit_coords(t_data *data)
{
	data->textures.digit_coords[0] = (t_vector){250, 225};
	data->textures.digit_coords[1] = (t_vector){300, 225};
	data->textures.digit_coords[2] = (t_vector){0, 300};
	data->textures.digit_coords[3] = (t_vector){50, 300};
	data->textures.digit_coords[4] = (t_vector){100, 300};
	data->textures.digit_coords[5] = (t_vector){150, 300};
	data->textures.digit_coords[6] = (t_vector){200, 300};
	data->textures.digit_coords[7] = (t_vector){250, 300};
	data->textures.digit_coords[8] = (t_vector){300, 300};
	data->textures.digit_coords[9] = (t_vector){0, 375};
}

/**
 * @brief Loads all UI elements, including icons and digits.
 */
static void	load_ui_elements(t_data *data)
{
	int			i;
	t_anim_info	info;

	init_digit_coords(data);
	i = 0;
	info.frame_count = 1;
	info.path = FONT_PATH;
	while (i < 10)
	{
		info.start_pos = data->textures.digit_coords[i];
		load_animation(data, &data->textures.ui_digits[i], info);
		i++;
	}
	load_animation(data, &data->textures.ui_key_icon, (t_anim_info){KEY_PATH,
		3, (t_vector){100, 0}});
	load_animation(data, &data->textures.ui_move_icon, (t_anim_info){MOVE_PATH,
		3, (t_vector){50, 0}});
	load_animation(data, &data->textures.ui_x_icon, (t_anim_info){FONT_PATH,
		3, (t_vector){100, 225}});
}
