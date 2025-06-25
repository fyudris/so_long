/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:46:54 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:20 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_path.c
 * @brief Validates if a map has a solvable path (Mandatory).
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

static void	flood_fill(char **grid, t_vector size, int x, int y);
static void	check_fill_results(char **original_grid, char **filled_grid,
				t_vector size);
static char	**duplicate_grid(char **original_grid, t_vector size);
static void	free_grid(char **grid, int height);

/**
 * @brief The main function to validate the map's path.
 * @details It orchestrates the path validation process:
 * 1. Creates a duplicate of the map grid to perform the fill on, leaving the
 * original map intact for rendering.
 * 2. Calls the recursive flood_fill function, starting at the player's position.
 * 3. After the fill, it checks the duplicated grid to ensure all collectibles
 * and the exit were reached.
 * 4. Frees the memory used by the duplicated grid.
 *
 * @param data A pointer to the main game data struct, which contains the map
 * and player's starting position.
 */
void	validate_path(t_data *data)
{
	char	**grid_copy;

	grid_copy = duplicate_grid(data->map.grid, data->map.size);
	flood_fill(grid_copy, data->map.size, data->player_pos.x,
		data->player_pos.y);
	check_fill_results(data->map.grid, grid_copy, data->map.size);
	free_grid(grid_copy, data->map.size.y);
}

/**
 * @brief Recursive flood-fill algorithm for the mandatory part.
 * @details This function "fills" an area of the map starting from (x, y).
 * It changes valid, reachable tiles ('0', 'C', 'E') to a special fill
 * character ('F'). The recursion then continues to all four adjacent tiles.
 * The fill is stopped by walls ('1') or by tiles that have already been
 * filled ('F'), preventing infinite loops.
 *
 * @param grid The map grid (a copy) to perform the fill on.
 * @param size The dimensions (width and height) of the map grid.
 * @param x The current x-coordinate to fill.
 * @param y The current y-coordinate to fill.
 */
static void	flood_fill(char **grid, t_vector size, int x, int y)
{
	if (x < 0 || x >= size.x || y < 0 || y >= size.y
		|| grid[y][x] == '1' || grid[y][x] == 'F')
		return ;
	grid[y][x] = 'F';
	flood_fill(grid, size, x + 1, y);
	flood_fill(grid, size, x - 1, y);
	flood_fill(grid, size, x, y + 1);
	flood_fill(grid, size, x, y - 1);
}

/**
 * @brief Checks if all required items were reached by the flood fill.
 * @details After the `flood_fill` is complete, this function iterates through
 * the original map. For every collectible ('C') and exit ('E') it finds,
 * it checks if the corresponding tile in the `filled_grid` was marked with 'F'.
 * If any 'C' or 'E' was not reached, the map is impossible to solve, and the
 * function exits with an error.
 *
 * @param original_grid The original, unmodified map grid.
 * @param filled_grid The map grid after being modified by `flood_fill`.
 * @param size The dimensions of the map grids.
 */
static void	check_fill_results(char **original_grid, char **filled_grid,
		t_vector size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if ((original_grid[y][x] == 'C' || original_grid[y][x] == 'E')
				&& filled_grid[y][x] != 'F')
				ft_print_error("Invalid path: Not all items are reachable.");
			x++;
		}
		y++;
	}
}

/**
 * @brief Creates a memory-allocated duplicate of the map grid.
 * @details A deep copy is necessary so the flood-fill algorithm can modify the
 * grid (by marking tiles with 'F') without changing the original map data
 * that will be used for rendering the game.
 *
 * @param original_grid The `char **` grid to be copied.
 * @param size The dimensions of the grid.
 * @return A new `char **` which is an exact copy of the original.
 */
static char	**duplicate_grid(char **original_grid, t_vector size)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * size.y);
	if (!copy)
		ft_print_error("Malloc failed during path validation.");
	i = 0;
	while (i < size.y)
	{
		copy[i] = ft_strdup(original_grid[i]);
		if (!copy[i])
		{
			free_grid(copy, i);
			ft_print_error("Malloc failed during path validation.");
		}
		i++;
	}
	return (copy);
}

/**
 * @brief A helper function to free a `char **` grid.
 * @details Iterates through the grid, freeing each row string before
 * freeing the top-level pointer.
 *
 * @param grid The `char **` grid to be freed.
 * @param height The number of rows in the grid.
 */
static void	free_grid(char **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
