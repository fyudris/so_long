/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 13:35:30 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Define keycodes for Linux (these may vary slightly)
#define KEY_ESC 65307

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
}   t_data;

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
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    data->win_ptr = NULL;
    exit(0);
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

    // --- NEW STUFF HERE ---
    // Register the keypress handler
    // mlx_key_hook is a simpler version of mlx_hook for key presses.
    mlx_key_hook(data.win_ptr, handle_keypress, &data);

    // Register the close button handler
    // The event code '17' corresponds to the 'DestroyNotify' event.
    // The mask '0' means no specific event mask.
    mlx_hook(data.win_ptr, 17, 0, handle_close_button, &data);
    // --- END OF NEW STUFF ---

    mlx_loop(data.mlx_ptr);

    return (0);
}