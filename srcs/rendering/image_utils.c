/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:54:29 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:12 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file image_utils.c
 * @brief Low-level utility functions for pixel manipulation.
 * @details This file contains the fundamental building blocks for image
 * rendering: getting and putting individual pixels. These functions are
 * separated into their own file to keep the main image.c file compliant
 * with the 5-function limit of the Norm.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Gets the color of a single pixel from a source image buffer.
 * @details Calculates the memory address of a specific pixel within the
 * raw image data buffer and returns its color value. It includes boundary
 * checks to prevent reading outside the image.
 *
 * @param img The source image struct containing the pixel data and dimensions.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The color of the pixel as an unsigned integer, or 0 if out of bounds.
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
 * @details Calculates the memory address for a specific pixel within the
 * destination buffer and writes the given color value to it. It includes
 * boundary checks to prevent writing outside the image.
 *
 * @param img The destination image struct.
 * @param x The x-coordinate of the pixel to place.
 * @param y The y-coordinate of the pixel to place.
 * @param color The color value to write.
 */
void	put_pixel_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel_address;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel_address = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel_address = color;
}
