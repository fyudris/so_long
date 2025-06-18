/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:44:04 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/18 11:21:45 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Gets the color of a single pixel from a source image buffer.
 */
unsigned int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel_address;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel_address = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel_address);
}

/**
 * @brief Puts a pixel of a given color into a destination image buffer.
 */
void	put_pixel_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel_address;
	
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel_address = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel_address = color;
}

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
void	unpack_sprite(t_img *dest, t_img *src, t_vector pos)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < dest->height)
	{
		x = -1;
		while (++x < dest->width)
		{
			color = get_pixel_from_img(src, pos.x + x, pos.y + y);
			put_pixel_to_img(dest, x, y, color);
		}
	}
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
