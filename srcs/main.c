/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 13:26:05 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Define some constants for window size
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// We need a structure to hold our mlx pointers
typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
}   t_data;

int main(void)
{
    t_data  data;

    // 1. Initialize the library
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1); // Error

    // 2. Create the window
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My First Window!");
    if (data.win_ptr == NULL)
    {
        // In case of error, you should clean up what was already created
        return (1);
    }

    // 3. Start the event loop
    mlx_loop(data.mlx_ptr);

    // The program will not reach here until the window is closed.
    return (0);
}