/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:47 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 20:35:34 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_content_bonus.c
 * @brief Functions for validating the content of the parsed map (Bonus).
 * @details This file checks for enclosing walls, valid characters, and the
 * correct number of players, exits, and collectibles for the bonus version.
 */

#include "../../include/so_long.h"

static void	check_walls_bonus(t_data *data);
static void	count_components_bonus(t_data *data);
static int	is_valid_char_bonus(char c);
static void	process_tile_bonus(t_data *data, int y, int x);

/**
 * @brief The main function to validate the map's content for the bonus part.
 */
void	validate_map_content(t_data *data)
{
	check_walls_bonus(data);
	count_components_bonus(data);
	if (data->map.players != 1)
		ft_print_error("Map must have exactly one starting position ('P').");
	if (data->map.collectibles < 1)
		ft_print_error("Map must have at least one collectible ('C').");
	if (data->map.exits != 1)
		ft_print_error("Map must have exactly one exit ('E').");
}

/**
 * @brief Processes a single tile of the map for the bonus version.
 * @details This helper function validates the character and updates the
 * counts for players, collectibles, or exits.
 *
 * @param data The main data struct.
 * @param y The row index of the tile.
 * @param x The column index of the tile.
 */
static void	process_tile_bonus(t_data *data, int y, int x)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (!is_valid_char_bonus(tile))
		ft_print_error("Map contains invalid characters.");
	if (tile == 'P')
	{
		data->map.players++;
		data->player_pos.x = x;
		data->player_pos.y = y;
		data->map.grid[y][x] = '0';
	}
	else if (tile == 'C')
		data->map.collectibles++;
	else if (tile == 'E')
		data->map.exits++;
}

/**
 * @brief Iterates through the map grid to count components for the
 * bonus version.
 * @details This function loops through each tile and calls the
 * `process_tile_bonus` helper to handle the logic for each one.
 * @param data A pointer to the main data struct.
 */
static void	count_components_bonus(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.size.y)
	{
		x = 0;
		while (x < data->map.size.x)
		{
			process_tile_bonus(data, y, x);
			x++;
		}
		y++;
	}
}

/**
 * @brief Checks if a character is valid for the BONUS map.
 * @details This is the permissive version that allows all game and text objects.
 */
static int	is_valid_char_bonus(char c)
{
	const char	*valid_chars;

	valid_chars = "01PCEWRpceuwryniso";
	if (ft_strchr(valid_chars, c))
		return (1);
	return (0);
}

/**
 * @brief Checks if the map is properly enclosed by walls ('1').
 * @details This function is identical to the mandatory version.
 *
 * @param data A pointer to the main game data struct.
 */
static void	check_walls_bonus(t_data *data)
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
			if (data->map.grid[y][0] != '1'
				|| data->map.grid[y][data->map.size.x - 1] != '1')
				ft_print_error("Map is not enclosed by walls.");
		}
		y++;
	}
}
