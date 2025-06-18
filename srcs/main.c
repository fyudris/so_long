/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/18 13:47:40 by fyudris          ###   ########.fr       */
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
	ft_printf("Checkpoint 1: Initializing data...\n");
	init_game_data(&data);

	ft_printf("Checkpoint 2: Parsing map...\n");
	parse_map(argv[1], &data);

	ft_printf("Checkpoint 3: Initializing MLX...\n");
	init_mlx(&data);

	ft_printf("Checkpoint 4: Loading all textures...\n");
	load_all_textures(&data);
	ft_printf("Checkpoint 5: All textures loaded. Setting up hooks...\n");

	mlx_hook(data.win, 17, 0, handle_close_window, &data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);

	ft_printf("Checkpoint 6: Starting MLX loop...\n");
	mlx_loop(data.mlx);
	return (0);
}
