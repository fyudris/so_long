/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:23:22 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 16:47:27 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	set_rule(t_data *data, char noun, char property);

/**
 * @brief Checks for a 3-block sentence at a given coordinate.
 *
 * This function looks for a "NOUN IS PROPERTY" pattern both horizontally and
 * vertically around a given 'IS' block. If a valid sentence is found, it
 * calls a helper to set the corresponding rule.
 *
 * @param data The main data struct.
 * @param x The x-coordinate of the 'IS' block.
 * @param y The y-coordinate of the 'IS' block.
 */
static void	check_sentence_at(t_data *data, int x, int y)
{
	if (x > 0 && x < data->map.size.x - 1)
		set_rule(data, data->map.grid[y][x - 1], data->map.grid[y][x + 1]);
	if (y > 0 && y < data->map.size.y - 1)
		set_rule(data, data->map.grid[y - 1][x], data->map.grid[y + 1][x]);
}

/**
 * @brief Scans the entire map for text blocks and updates the game rules.
 *
 * This function is the heart of the "Baba Is You" mechanic. It is called once
 * at the start of the game and then again after every successful push.
 * It first resets all dynamic rules to their default "solid" state, then
 * re-applies any rules currently formed on the map.
 *
 * @param data The main game data struct.
 */
void	update_game_rules(t_data *data)
{
	int	x;
	int	y;

	data->rules.wall_is_pushable = false;
	data->rules.key_is_activated = false;
	data->rules.rock_is_pushable = false;
	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			if (data->map.grid[y][x] == 'i')
				check_sentence_at(data, x, y);
		}
	}
}

/**
 * @brief Sets a specific game rule based on a detected sentence.
 *
 * @param data The main data struct.
 * @param noun The character for the NOUN text block
 * (e.g., 'w' for WALL).
 * @param property The character for the PROPERTY text block
 * (e.g., 'u' for PUSH).
 */
static void	set_rule(t_data *data, char noun, char property)
{
	if (noun == 'w' && property == 'u')
		data->rules.wall_is_pushable = true;
	if (noun == 'c' && property == 'o')
		data->rules.key_is_activated = true;
	if (noun == 'r' && property == 'u')
		data->rules.rock_is_pushable = true;
}

/**
 * @brief Handles the logic for pushing an object.
 *
 * This function is now safer. It first checks if the destination "behind"
 * the object is within the map boundaries. Only then does it check if that
 * tile is empty. This prevents out-of-bounds memory access and crashes.
 *
 * @param data The main data struct.
 * @param obj_pos The current position of the object to be pushed.
 * @return true if the push was successful, false otherwise.
 */
bool	handle_push(t_data *data, t_vector obj_pos)
{
	t_vector	behind_pos;
	char		obj_char;

	behind_pos = obj_pos;
	if (data->player_dir == UP)
		behind_pos.y -= 1;
	else if (data->player_dir == DOWN)
		behind_pos.y += 1;
	else if (data->player_dir == LEFT)
		behind_pos.x -= 1;
	else if (data->player_dir == RIGHT)
		behind_pos.x += 1;
	if (behind_pos.y < 0 || behind_pos.y >= data->map.size.y
		|| behind_pos.x < 0 || behind_pos.x >= data->map.size.x)
		return (false);
	if (data->map.grid[behind_pos.y][behind_pos.x] == '0')
	{
		obj_char = data->map.grid[obj_pos.y][obj_pos.x];
		data->map.grid[behind_pos.y][behind_pos.x] = obj_char;
		data->map.grid[obj_pos.y][obj_pos.x] = '0';
		update_game_rules(data);
		return (true);
	}
	return (false);
}
