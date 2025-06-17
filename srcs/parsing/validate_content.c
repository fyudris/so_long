/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:47 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 13:33:53 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

/**
 * @brief Checks if the map is properly enclsed by walls ('1')
 * 
 * @param data A pointer to the main game data struct
 */
static void	check_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.size.y)
	{
		// For the very first and very last row, check every character.
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
			// For all middle rows, only check the first and last characters.
			if (data->map.grid[y][0] != '1' ||
				data->map.grid[y][data->map.size.x - 1] != '1')
				ft_print_error("Map is not enclosed by walls.");
		}
		y++;
	}
}

/**
 * @brief Checks if a character is a valid map content.
 * 
 * It checks a character against the list of all allowed characters for the 
 * game, including game objects and all pushable text blocks.
 * 
 * | Character | so_long Component | Your Game's Object                |
 * |-----------|-------------------|-----------------------------------|
 * | 1         | Wall              | Fort (Enclosing Wall)             |
 * | 0         | Empty Space       | Empty Space                       |
 * | P         | Player Start      | Baba                              |
 * | C         | Collectible       | Key (The Item to Collect)         |
 * | E         | Map Exit          | Door (The Final Exit)             |
 * | D         | Custom Obstacle   | Door (Obstacle)                   |
 * | W         | Custom Obstacle   | Wall (Obstacle)                   |
 * | R         | Custom Obstacle   | Rock (Obstacle)                   |
 * | K         | Custom Object     | Key (Pushable Object)             |
 * | b, y      | Static Text       | "BABA", "YOU"                     |
 * | d, n      | Static Text       | "DOOR", "WIN"                     |
 * | i         | Pushable Text     | "IS"                              |
 * | k, w, r   | Pushable Text     | "KEY", "WALL", "ROCK"             |
 * | o, p, s   | Pushable Text     | "OPEN", "PUSH", "STOP"            |
 * 
 * @return int Returns 1 if valid, 0 otherwise.
 * 
 */
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E' ||
		c == 'D' || c == 'W' || c == 'R' || c == 'K' || c == 'b' ||
		c == 'w' || c == 'k' || c == 'r' || c == 'd' || c == 's' ||
		c == 'o' || c == 'p' || c == 'n' || c == 'y' || c == 'i');
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
				ft_print_error("Map contains invalid characters.");
			if (data->map.grid[y][x] == 'P')
			{
				data->map.players++;
				data->player_pos.x = x;
				data->player_pos.y = y;
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