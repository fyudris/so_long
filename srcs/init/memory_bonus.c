/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:45:29 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:44 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file memory_bonus.c
 * @brief Memory management functions for the BONUS version of so_long.
 *
 * @details This file is responsible for safely freeing all dynamically
 * allocated memory for the full-featured bonus version of the game.
 * It handles all assets, including UI elements and text-block sprites.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Frees all memory associated with a single animation sequence.
 *
 * @details This is a helper function that iterates through each frame of a
 * `t_animation` struct. For each frame, it calls `mlx_destroy_image`
 * to release the memory managed by the MiniLibX library. After all
 * image pointers are destroyed, it frees the `anim->frames` array itself.
 *
 * @param data A pointer to the main `t_data` struct.
 * @param anim A pointer to the `t_animation` struct to be freed.
 */
static void	free_animation(t_data *data, t_animation *anim)
{
	int	i;

	if (anim && anim->frames)
	{
		i = 0;
		while (i < anim->frame_count)
		{
			if (anim->frames[i].ptr)
				mlx_destroy_image(data->mlx, anim->frames[i].ptr);
			i++;
		}
		free(anim->frames);
	}
}

/**
 * @brief Frees the memory allocated for the 2D map grid.
 *
 * @details Iterates through the `char **` grid, freeing each row string
 * before freeing the top-level array.
 *
 * @param map A pointer to the `t_map` struct containing the grid.
 */
static void	free_map_grid(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->size.y)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

/**
 * @brief Frees all textures related to game objects and text blocks.
 *
 * @details This helper function is called by `cleanup_and_exit` to handle
 * freeing the large number of bonus-specific sprite animations, keeping
 * the main cleanup function within the 25-line limit.
 *
 * @param data A pointer to the main `t_data` struct.
 */
static void	free_game_textures(t_data *data)
{
	free_animation(data, &data->textures.player_txt);
	free_animation(data, &data->textures.wall);
	free_animation(data, &data->textures.wall_txt);
	free_animation(data, &data->textures.key_txt);
	free_animation(data, &data->textures.door_txt);
	free_animation(data, &data->textures.rock);
	free_animation(data, &data->textures.rock_txt);
	free_animation(data, &data->textures.you_txt);
	free_animation(data, &data->textures.open_txt);
	free_animation(data, &data->textures.push_txt);
	free_animation(data, &data->textures.win_txt);
	free_animation(data, &data->textures.is_txt);
}

/**
 * @brief Frees all textures related to the graphical user interface (UI).
 *
 * @details This helper is called by `cleanup_and_exit` to handle freeing
 * the UI icons and the array of digit sprites.
 *
 * @param data A pointer to the main `t_data` struct.
 */
static void	free_ui_textures(t_data *data)
{
	int	i;

	free_animation(data, &data->textures.ui_move_icon);
	free_animation(data, &data->textures.ui_key_icon);
	free_animation(data, &data->textures.ui_x_icon);
	i = -1;
	while (++i < 10)
		free_animation(data, &data->textures.ui_digits[i]);
}

/**
 * @brief The centralized cleanup function for the BONUS version.
 *
 * @details This function is the single point of exit for the program, ensuring
 * that all allocated resources are released in the correct order to prevent
 * memory leaks.
 *
 * @param data A pointer to the main `t_data` struct containing all resources.
 * @param status The exit code to be returned to the shell (0 for success).
 */
void	cleanup_and_exit(t_data *data, int status)
{
	if (!data)
		exit(status);
	free_animation(data, &data->textures.player_down);
	free_animation(data, &data->textures.player_up);
	free_animation(data, &data->textures.player_left);
	free_animation(data, &data->textures.player_right);
	free_animation(data, &data->textures.fort_wall);
	free_animation(data, &data->textures.key);
	free_animation(data, &data->textures.door);
	free_game_textures(data);
	free_ui_textures(data);
	free_map_grid(&data->map);
	if (data->game_buffer.ptr)
		mlx_destroy_image(data->mlx, data->game_buffer.ptr);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}
