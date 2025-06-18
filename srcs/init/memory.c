/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:45:29 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 21:08:48 by fyudris          ###   ########.fr       */
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
	free_animation(data, &data->textures.fort_wall);
	free_animation(data, &data->textures.key);
	// ... add a call here for EVERY texture you have ...

	// ... Free map grid, destroy window, destroy display ...
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}
