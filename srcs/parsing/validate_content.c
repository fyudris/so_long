/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:45:23 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 20:49:20 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_content.c
 * @brief Functions for validating the content of the parsed map (Mandatory).
 */

#include "../../include/so_long.h"

static void	check_walls(t_data *data);
static void	count_components(t_data *data);
static int	is_valid_char(char c);

/**
 * @brief Main function to validate the map's content for the mandatory part.
 */
void	validate_map_content(t_data *data)
{
	check_walls(data);
	count_components(data);
	if (data->map.players != 1)
		ft_print_error("Map must have exactly one starting position ('P').");
	if (data->map.collectibles < 1)
		ft_print_error("Map must have at least one collectible ('C').");
	if (data->map.exits != 1)
		ft_print_error("Map must have exactly one exit ('E').");
}

/**
 * @brief Checks if a character is valid for the MANDATORY map.
 * @details This is the strict version that only allows '0', '1', 'P', 'C', 'E'.
 */
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

static void	check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.size.y)
	{
		if (y == 0 || y == data->map.size.y - 1)
		{
			x = 0;
			while (x < data->map.size.x)
				if (data->map.grid[y][x++] != '1')
					ft_print_error("Map is not enclosed by walls.");
		}
		else
		{
			if (data->map.grid[y][0] != '1' ||
				data->map.grid[y][data->map.size.x - 1] != '1')
				ft_print_error("Map is not enclosed by walls.");
		}
		y++;
	}
}

static void	count_components(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.size.y)
	{
		x = 0;
		while (x < data->map.size.x)
		{
			if (!is_valid_char(data->map.grid[y][x]))
				ft_print_error("Map contains invalid characters.");
			if (data->map.grid[y][x] == 'P')
			{
				data->map.players++;
				data->player_pos.x = x;
				data->player_pos.y = y;
				data->map.grid[y][x] = '0';
			}
			else if (data->map.grid[y][x] == 'C')
				data->map.collectibles++;
			else if (data->map.grid[y][x] == 'E')
				data->map.exits++;
			x++;
		}
		y++;
	}
}
