/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:46:54 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 20:47:21 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_path.c
 * @brief Validates if a map has a solvable path (Mandatory).
 */

#include "../../include/so_long.h"

static void	flood_fill(char **grid, t_vector size, int x, int y);
static void	check_fill_results(char **original_grid, char **filled_grid,
				t_vector size);
static char	**duplicate_grid(char **original_grid, t_vector size);
static void	free_grid(char **grid, int height);

/**
 * @brief Main function to validate the mandatory map's path.
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
 * @brief Simple flood-fill that stops only at walls ('1').
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
