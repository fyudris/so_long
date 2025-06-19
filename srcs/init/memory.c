/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:45:29 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/19 15:19:10 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief A helper to free one animation sequence's allocated memory.
 */
static void	free_animation(t_data *data, t_animation *anim)
{
	int	i;

	if (anim && anim->frames)
	{
		i = 0;
		// First, destroy each individual image frame in the animation
		while (i < anim->frame_count)
		{
			if (anim->frames[i].ptr)
				mlx_destroy_image(data->mlx, anim->frames[i].ptr);
			i++;
		}
		// Then, free the array that held the pointers to those frames
		free(anim->frames);
	}
}

/**
 * @brief Frees all memory associated with the map.grid (char **).
 *
 * It loops through each row, freeing the string, and then frees the
 * array of pointers itself.
 *
 * @param map A pointer to the t_map struct.
 */
static void	free_map_grid(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->size.y)
	{
		// Free each individual line (string)
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	// Free the array of pointers
	free(map->grid);
	map->grid = NULL;
}

/**
 * @brief The centralized cleanup function to free all allocated memory.
 * This has been updated to use the free_animation helper.
 */
void	cleanup_and_exit(t_data *data, int status)
{
	if (!data)
		exit(status);
	// Free every animation struct
	free_animation(data, &data->textures.player_down);
	free_animation(data, &data->textures.player_up);
	free_animation(data, &data->textures.player_left);
	free_animation(data, &data->textures.player_right);
	free_animation(data, &data->textures.player_txt);
	free_animation(data, &data->textures.wall);
	free_animation(data, &data->textures.wall_txt);
	free_animation(data, &data->textures.fort_wall);
	free_animation(data, &data->textures.key);
	free_animation(data, &data->textures.key_txt);
	free_animation(data, &data->textures.door);
	free_animation(data, &data->textures.door_txt);
	free_animation(data, &data->textures.rock);
	free_animation(data, &data->textures.rock_txt);
	free_animation(data, &data->textures.you_txt);
	free_animation(data, &data->textures.open_txt);
	free_animation(data, &data->textures.push_txt);
	free_animation(data, &data->textures.win_txt);
	free_animation(data, &data->textures.is_txt);

	// ... Free map grid, destroy window, destroy display ...
	free_map_grid(&data->map);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}
