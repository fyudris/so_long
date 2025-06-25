/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:45:23 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:29 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_content.c
 * @brief Functions for validating the content of the parsed map (Mandatory).
 * @details This file checks for enclosing walls, valid characters, and the
 * correct number of players, exits, and collectibles.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void	check_walls(t_data *data);
static void	count_components(t_data *data);
static int	is_valid_char(char c);
static void	process_tile(t_data *data, int y, int x);

/**
 * @brief The main function to validate the map's content for the mandatory part.
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
 * @brief Processes a single tile of the map.
 * @details This helper function is called by `count_components`. It validates
 * the character at the given (y, x) coordinate and updates the counts for
 * players, collectibles, or exits accordingly. It also sets the player's
 * initial position. This refactoring keeps `count_components` within the
 * 25-line limit required by the Norm.
 *
 * @param data The main data struct.
 * @param y The row index of the tile.
 * @param x The column index of the tile.
 */
static void	process_tile(t_data *data, int y, int x)
{
	char	tile;

	tile = data->map.grid[y][x];
	if (!is_valid_char(tile))
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
 * @brief Iterates through the map grid to count components.
 * @details This function now acts as a simple iterator, looping through each
 * tile of the map and passing its coordinates to the `process_tile`
 * helper function, which handles the actual logic.
 *
 * @param data A pointer to the main data struct.
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
			process_tile(data, y, x);
			x++;
		}
		y++;
	}
}

/**
 * @brief Checks if a character is valid for the Mandatory map.
 * @details This is the  version that allows only the wall, player,
 * exit, and collectible game objects.
 */
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E')
		return (1);
	return (0);
}

/**
 * @brief Checks if the map is properly enclosed by walls ('1').
 *
 * @param data A pointer to the main game data struct.
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
