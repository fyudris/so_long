/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:49:49 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:24 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Creates a deep copy of the map grid.
 *
 * A deep copy is necessary so the flood fill algorithm can modify the map
 * (by marking visited tiles) without destroying the original map data needed
 * for rendering the game.
 *
 * @param data A pointer to the main game data struct.
 * @return A new char** which is a copy of the map grid.
 */
static char	**copy_map_grid(t_data *data)
{
	char	**grid_copy;
	int		i;

	grid_copy = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!grid_copy)
		ft_print_error("Memory allocation failed for map copy.");
	i = 0;
	while (i < data->map.size.y)
	{
		grid_copy[i] = ft_strdup(data->map.grid[i]);
		if (!grid_copy[i])
		{
			while (--i >= 0)
				free(grid_copy[i]);
			free(grid_copy);
			ft_print_error("Memory allocation failed for map copy line.");
		}
		i++;
	}
	grid_copy[i] = NULL;
	return (grid_copy);
}

/**
 * @brief The recursive flood fill algorithm.
 *
 * This function "fills" an area starting from (x,y). It marks the current
 * tiles as visited ('F') and then recursively calls itself for adjacent tiles.
 * The recursion stops when it hits a wall ('1') or an already-filled tile ('F').
 *
 * @param map_copy The copy of the map grid to be filled.
 * @param size The dimensions of the map.
 * @param pos The current (x, y) coordinates to fill
 */
static void	flood_fill(char **map_copy, t_vector size, t_vector pos)
{
	if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x
		|| map_copy[pos.y][pos.x] == '1'
		|| map_copy[pos.y][pos.x] == 'F')
		return ;
	map_copy[pos.y][pos.x] = 'F';
	flood_fill(map_copy, size, (t_vector){pos.x, pos.y + 1});
	flood_fill(map_copy, size, (t_vector){pos.x, pos.y - 1});
	flood_fill(map_copy, size, (t_vector){pos.x + 1, pos.y});
	flood_fill(map_copy, size, (t_vector){pos.x - 1, pos.y});
}

/**
 * @brief Checks if all collectibles and the exit were reached by flood fill.
 *
 * After the flood fill is complete, this function iterates through the original
 * map. For every 'C' and 'E', it checks if the corresponding tile in the
 * copied map was marked as 'F' (Filled). If any were not, it means there is
 * no valid path.
 *
 * @param data A pointer to the main game data struct.
 * @param map_copy The filled copy of the map grid.
 */
static void	check_path(t_data *data, char **map_copy)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < data->map.size.y)
	{
		x = 0;
		while (x < data->map.size.x)
		{
			if ((data->map.grid[y][x] == 'C' || data->map.grid[y][x] == 'E')
				&& map_copy[y][x] != 'F')
				ft_print_error("No valid path to collectibles or the exit.");
			x++;
		}
		y++;
	}
	i = 0;
	while (i < data->map.size.y)
		free(map_copy[i++]);
	free(map_copy);
}

/**
 * @brief Validates that a path exists from the player to all items.
 *
 * This is the main orchestrator for the path validation step. It copies the
 * map, runs the flood fill from the player's start, and then checks the result.
 *
 * @param data A pointer to the main game data struct.
 */
void	validate_path(t_data *data)
{
	char	**map_copy;

	map_copy = copy_map_grid(data);
	flood_fill(map_copy, data->map.size, data->player_pos);
	check_path(data, map_copy);
}
