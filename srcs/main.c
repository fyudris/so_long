/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 18:53:19 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// static void	print_map(t_data *data)
// {
// 	int	y;

// 	if (!data->map.grid)
// 		return ;
// 	ft_printf("--- Map Read ---\n");
// 	ft_printf("Width: %d, Height: %d\n", data->map.size.x, data->map.size.y);
// 	y = 0;
// 	while (y < data->map.size.y)
// 	{
// 		ft_printf("%s\n", data->map.grid[y]);
// 		y++;
// 	}
// 	ft_printf("----------------\n");
// }

/**
 * @brief The main entry point of the so_long program.
 *
 * This function is responsible for:
 * 1. Validating command-line arguments.
 * 2. Initializing all game data structures.
 * 3. Parsing and validating the provided map file.
 * 4. Initializing the MiniLibX graphics system and window.
 * 5. Loading all game textures.
 * 6. Registering all event hooks (keyboard, window close).
 * 7. Starting the main game loop.
 */
int	main(int argc, char **argv)
{
	t_data	data;

	// 1. Argument & Data Setup
	if (argc != 2)
	{
		// Note: Using ft_putstr_fd for simple strings is more efficient
		// than ft_printf for this error message.
		ft_putstr_fd("Error\nUsage: ./so_long maps/your_map.ber\n", 2);
		return (1);
	}
	init_game_data(&data);

	// 2. Map Parsing
	// This function will read the file and validate the map's geometry,
	// content, and path. It will exit with an error if anything is wrong.
	parse_map(argv[1], &data);

	// 3. Graphics & Asset Setup
	// These functions set up the MLX connection, create the window
	// based on the map's dimensions, and load all .xpm sprites.
	init_mlx(&data);
	load_all_textures(&data);

	// 4. Register Hooks
	// Tell MLX which functions to call when specific events happen.
	// This fulfills the mandatory requirements for closing the window
	// and for player movement. 
	mlx_hook(data.win, 17, 0, handle_close_window, &data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);

	// 5. Start Game
	// This function starts the event loop. It will not return until
	// the game is closed. All updates will now happen in your hook functions.
	mlx_loop(data.mlx);
	return (0);
}
