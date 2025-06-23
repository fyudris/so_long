/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:08 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 01:06:36 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file memory.c
 * @brief Memory management and cleanup functions for the so_long game.
 * @details This file contains the functions responsible for safely freeing all
 * dynamically allocated memory before the program exits. This includes
 * MLX images, window/display pointers, and the map grid. This is the
 * MANDATORY version, which only handles the assets required by the subject.
 */
#include "../../include/so_long.h"

/**
 * @brief Frees all memory associated with a single animation sequence.
 * 
 * @details This is a helper function that iterates through each frame of a
 * `t_animation` struct. For each frame, it calls `mlx_destroy_image`
 * to release the memory managed by the MiniLibX library. After all
 * image pointers are destroyed, it frees the `anim->frames` array itself. 
 *
 * @param data A pointer to the main `t_data` struct
 * @param anim A pointer to the `t_animation` struct to be freed
 */
static void	free_animation(t_data *data, t_animation *anim)
{
	int	i;

	if (data && data->mlx && anim && anim->frames)
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
 * @details The map grid is a `char **` (an array of strings). This function
 * iterates through each row of the array, freeing each individual string
 * (each `char *`). After all rows are freed, it frees the top-level
 * pointer to the array of pointers. Finally, it sets the grid pointer
 * to NULL to prevent dangling pointer issues.
 *
 * @param map A pointer to the `t_map` struct containing the grid to be freed
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
 * @brief The centralized cleanup function to free all allocated memory and
 * exit.
 * 
 * @details This function is the single point of exit for the program, ensuring
 * that all allocated resources are released in the correct order to prevent
 * memory leaks. It is called when the game ends, the window is closed,
 * or an error occurs.
 *
 * It frees:
 * 1.  All mandatory game textures (Player, Wall, Key, Door).
 * 2.  The `char **` map grid.
 * 3.  The off-screen `game_buffer` image.
 * 4.  The MLX window.
 * 5.  The MLX display connection, which is the final MLX resource to be freed.
 *
 * After cleanup, it calls `exit()` with the given status code.
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
