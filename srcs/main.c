/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 14:44:13 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief This function is called when a key is pressed.
 *
 * @param keycode The code of the key that was pressed.
 * @param data A pointer to our custom data structure.
 * @return int Always return 0.
 */
int handle_keypress(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL; // It's good practice to NULL a freed pointer
        exit(0); // A simple way to exit the program
    }
    return (0);
}

/**
 * @brief This function is called when the red 'X' is clicked.
 */
int handle_close_button(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    data->win_ptr = NULL;
    exit(0);
    return (0);
}

/**
 * @brief Put a pixel of a specific color into our image buffer
 */
void    ft_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    // Calculate the memory address of the pixel at (x, y)
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

/**
 * @brief Main rendering function. It will be called repeatedly in a loop.
 */
int render_frame(t_data *data)
{
    int color;
    int x;
    int y;
    
    // Don't do anything if the window is closed
    if (data->win_ptr == NULL)
        return (1);
    
    // Draw a 50x50 red square
    color = 0x00FF0000; // Redin 0x00RRGGBB format

    y = 50;
    while (y < 100)
    {
        x = 50;
        while (x < 100)
        {
            ft_pixel_put(&data->img, x, y, color);
            x++;
        }
        y++;
    }
    // Push the entire image to the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Closable Window");
    if (!data.win_ptr)
        return (1);

    // 1. Create the image we will dra on
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!data.img.img_ptr)
        return (1);
    data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);

    // Register the keypress handler
    mlx_key_hook(data.win_ptr, handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 0, handle_close_button, &data);
    

    // 2. Register the render_frame function to be called in a loop
    mlx_loop_hook(data.mlx_ptr, render_frame, &data);
    
    mlx_loop(data.mlx_ptr);

    return (0);
}