/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:47 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 01:51:43 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_content.c
 * @brief Functions for validating the content of the parsed map.
 * 
 * @details This file contains the logic to ensure the map adheres to the
 * game's structural rules after it has been loaded into a 2D grid. It
 * checks for enclosing walls, valid characters, and the correct number
 * of players, exits, and collectibles.
 */

#include "../../include/so_long.h"

/**
 * @brief Checks if the map is properly enclosed by walls ('1').
 *
 * @param data A pointer to the main game data struct containing the map.
 */
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
			{
				if (data->map.grid[y][x++] != '1')
					ft_print_error("Map is not enclosed by walls.");
			}
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

/**
 * @brief Checks if a character is a valid map component.
 * @details This function validates a character by checking if it exists 
 * within a predefined string of all allowed characters. 
 * This list includes both mandatory (`0`, `1`, `P`, `C`, `E`) and bonus 
 * characters (text blocks).
 *
 * @param c The character to check.
 * @return int Returns 1 if the character is valid, 0 otherwise.
 */
static int	is_valid_char(char c)
{
	const char	*valid_chars;
	valid_chars = "01PCEWRpceuwryniso";
	if (ft_strchr(valid_chars, c))
		return (1);
	return (0);
}

/**
 * @brief Counts mandatory components and validates all characters in the map.
 * 
 * This function itearates through every tile of the map to do two things:
 * 	1. Ensure every character is valid by calling is_valid_char()
 * 	2. Count the number of player ('P'), collectibles ('C'), and exits ('E')
 * 
 * It also has the important sid-effect of setting the player's initial
 * coordinates in the main data struct when it finds the 'P'.
 * 
 * @param data A pointer to the main data struct
 * 
 */
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
				ft_printf("Map contains invalid characters. %c\n", 
					data->map.	grid[y][x]);
			if (data->map.grid[y][x] == 'P')
			{
				data->map.players++;
				data->player_pos.x = x;
				data->player_pos.y = y;
				// Once we have the player's start position, we replace the 'P'
				// with an empty floor tile so we don't draw it later.
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

void	validate_map_content(t_data *data)
{
	check_walls(data);
	count_components(data);
	if (data->map.players !=  1)
		ft_print_error("Map must contain exactly one starting position ('P').");
	if (data->map.collectibles < 1)
		ft_print_error("Map must contain at least one collectible ('C').");
	if (data->map.exits != 1)
		ft_print_error("Map must contain exactly one exit ('E').");
}