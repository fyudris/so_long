/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:44:57 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 14:27:31 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include "../libft/includes/ft_printf.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define KEY_ESC 65307

typedef struct s_img
{
    void    *img_ptr;
    char    *addr; // Pointer to the start of the image data
    int     bpp; // Bits per pixel
    int     line_len; // Size of one line in bytes
    int     endian; // 0 for littel endian, 1 for big endian
}   t_img;

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_img   img; // Add the our image structure here
}   t_data;

#endif