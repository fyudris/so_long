/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:04:09 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:47:33 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file render_utils_bonus.c
 * @brief Utility functions for the bonus rendering engine.
 * @details This file contains helper functions that are called by the main
 * render loop. Separating them here keeps the main file compliant with
 * the 5-function limit of the Norm.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static t_animation	*get_text_block_anim(t_data *data, char tile_type);

/**
 * @brief Draws a single digit sprite to the screen.
 */
void	draw_one_digit(t_data *data, char digit_char, t_vector pos)
{
	int	digit;

	digit = digit_char - '0';
	if (data->textures.ui_digits[digit].frames)
		mlx_put_image_to_window(data->mlx, data->win,
			data->textures.ui_digits[digit].frames[0].ptr, pos.x, pos.y);
}

/**
 * @brief Draws a number to the screen using loaded digit sprites.
 */
void	draw_number(t_data *data, int n, t_vector pos)
{
	char	*str_num;
	int		i;

	if (n == 0)
	{
		draw_one_digit(data, '0', pos);
		return ;
	}
	str_num = ft_itoa(n);
	if (!str_num)
		return ;
	i = 0;
	while (str_num[i])
	{
		draw_one_digit(data, str_num[i],
			(t_vector){pos.x + (i * TILE_SIZE), pos.y});
		i++;
	}
	free(str_num);
}

/**
 * @brief Returns the animation for game object characters ('C', 'E', 'W', 'R').
 */
t_animation	*get_object_anim(t_data *data, char tile_type)
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
	return (get_text_block_anim(data, tile_type));
}

/**
 * @brief Returns the animation for text block characters ('p', 'y', 'n', etc.).
 */
static t_animation	*get_text_block_anim(t_data *data, char tile_type)
{
	if (tile_type == 'p')
		return (&data->textures.player_txt);
	if (tile_type == 'y')
		return (&data->textures.you_txt);
	if (tile_type == 'n')
		return (&data->textures.win_txt);
	if (tile_type == 'o')
		return (&data->textures.open_txt);
	if (tile_type == 'u')
		return (&data->textures.push_txt);
	if (tile_type == 'i')
		return (&data->textures.is_txt);
	return (NULL);
}
