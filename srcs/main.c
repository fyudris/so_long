/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:33:00 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 12:58:24 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	print_map(t_data *data)
{
	int	y;

	if (!data->map.grid)
		return ;
	ft_printf("--- Map Read ---\n");
	ft_printf("Width: %d, Height: %d\n", data->map.size.x, data->map.size.y);
	y = 0;
	while (y < data->map.size.y)
	{
		ft_printf("%s\n", data->map.grid[y]);
		y++;
	}
	ft_printf("----------------\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_print_error("Usage: ./so_long maps/your_map.ber");
		return (1);
	}
	init_game_data(&data);
	parse_map(argv[1], &data);
	print_map(&data);
	return (0);
}
