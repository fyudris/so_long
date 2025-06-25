/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:44:04 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 21:39:34 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file image.c
 * @brief High-level functions for image and sprite manipulation.
 * @details This file contains the core logic for rendering operations like
 * unpacking sprites from a sheet, upscaling them, and drawing them to a
 * buffer. It relies on helper functions from image_utils.c for direct
 * pixel manipulation.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Copies a rectangular area of pixels from a source to a destination.
 * @details Iterates through a defined rectangle on the source spritesheet
 * and copies each pixel to the destination image, effectively "unpacking" a
 * single sprite.
 *
 * @param dest The destination image (must be pre-allocated).
 * @param src The source spritesheet.
 * @param pos The top-left (x,y) coordinate of the sprite on the source sheet.
 */
void	unpack_sprite(t_img *dest, t_img *src, t_vector pos)
{
	t_vector		p;
	unsigned int	color;

	p.y = -1;
	while (++p.y < dest->height)
	{
		p.x = -1;
		while (++p.x < dest->width)
		{
			color = get_pixel_from_img(src, pos.x + p.x, pos.y + p.y);
			put_pixel_to_img(dest, p.x, p.y, color);
		}
	}
}

/**
 * @brief Scales a small source image onto a larger destination image.
 * @details This function uses the "Nearest Neighbor" algorithm.
 *
 * @param dest The destination image (must be pre-allocated and larger).
 * @param src The source image (the small sprite).
 */
void	upscale_sprite(t_img *dest, t_img *src)
{
	t_vector	p;
	t_vector	scale_ratio;
	t_vector	src_p;

	scale_ratio.x = (src->width << 16) / dest->width;
	scale_ratio.y = (src->height << 16) / dest->height;
	p.y = 0;
	while (p.y < dest->height)
	{
		p.x = 0;
		while (p.x < dest->width)
		{
			src_p.x = (p.x * scale_ratio.x) >> 16;
			src_p.y = (p.y * scale_ratio.y) >> 16;
			put_pixel_to_img(dest, p.x, p.y,
				get_pixel_from_img(src, src_p.x, src_p.y));
			p.x++;
		}
		p.y++;
	}
}

/**
 * @brief Draws a small sprite onto a larger image buffer at a
 * specific coordinate.
 * @details This function "stamps" a texture onto the correct position on the
 * game's back buffer. It ignores transparent pixels (color 0) to allow
 * for layering sprites.
 *
 * @param buffer The large destination image buffer.
 * @param sprite The small source sprite image.
 * @param pos The top-left (x,y) pixel coordinate on the buffer to draw at.
 */
void	draw_sprite_to_buffer(t_img *buffer, t_img *sprite, t_vector pos)
{
	t_vector		p;
	unsigned int	color;

	p.y = 0;
	while (p.y < sprite->height)
	{
		p.x = 0;
		while (p.x < sprite->width)
		{
			color = get_pixel_from_img(sprite, p.x, p.y);
			if (color != 0x000000)
				put_pixel_to_img(buffer, pos.x + p.x, pos.y + p.y, color);
			p.x++;
		}
		p.y++;
	}
}

/**
 * @brief Fills an entire image buffer with a single color.
 * @details This is used to clear the back buffer each frame to prevent ghosting.
 * It uses `ft_memset` for maximum efficiency when clearing to black.
 *
 * @param img The image buffer to clear.
 * @param color The color to fill with (e.g., 0x000000 for black).
 */
void	clear_image_buffer(t_img *img, int color)
{
	int	x;
	int	y;

	if (color == 0x000000)
	{
		ft_memset(img->addr, 0, img->width * img->height * (img->bpp / 8));
		return ;
	}
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}
