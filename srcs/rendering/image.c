/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:44:04 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 19:08:46 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

// Get the color of a single pixel from a source image buffer
unsigned int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel_address;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel_address = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel_address);
}

// Puts a pixel of a given color into a destination image buffer.
void	put_pixel_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel_address;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel_address = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel_address = color;
}

/**
 * @brief Scales a small source image onto a larger destination image.
 *
 * This function uses the "Nearest Neighbor" algorithm to scale an image.
 * It iterates through every pixel of the large destination image, calculates
 * the corresponding source pixel, and copies its color.
 *
 * @param dest The destination image (must be pre-allocated and larger).
 * @param src The source image (the small sprite).
 */
void	upscale_sprite(t_img *dest, t_img *src)
{
	int	x;
	int	y;
	int	scale_x_ratio;
	int	scale_y_ratio;

	// Calculate the scaling ratio. Using fixed-point arithmetic for precision.
	// (src_width * 65536) / dest_width
	scale_x_ratio = (src->width << 16) / dest->width;
	scale_y_ratio = (src->height << 16) / dest->height;
	y = 0;
	while (y < dest->height)
	{
		x = 0;
		while (x < dest->width)
		{
			// Find the corresponding pixel in the source image
			int src_x = (x * scale_x_ratio) >> 16;
			int src_y = (y * scale_y_ratio) >> 16;
			// Copy the color
			put_pixel_to_img(dest, x, y, get_pixel_from_img(src, src_x, src_y));
			x++;
		}
		y++;
	}
}
