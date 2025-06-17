/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:54:15 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 14:16:02 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

 /**
  * @brief Reads the map from a file descriptor into a temporary list.
  * 
  * This function reads the map line by line, calculates dimensions, and stores
  * each line in a `t_list` for validation before final allocation.
  * 
  * @param fd
  * @param map_list_head
  * @param data
  */
static void	read_map_to_list(int fd, t_list **map_list_head, t_data *data)
{
	char	*line;
	int		is_first_line;

	is_first_line = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_first_line)
		{
			// Measure the length of first line
			data->map.size.x = ft_strlen(line);
			// Substract 1 if there's a '\n' at the end
			if (line[data->map.size.x - 1] == '\n')
				data->map.size.x--;
			is_first_line = 0;
		}
		ft_lstadd_back(map_list_head, ft_lstnew(line));
		data->map.size.y++;
	}
	if (data->map.size.y == 0)
		ft_print_error("Map file is empty.");
}

/**
 * @brief Converts the linked list map into a 2D char array (grid).
 *
 * This function allocates the final grid and copies data from the list.
 * It performs the final, crucial check to ensure the map is rectangular.
 *
 * @param head A pointer to the head of the linked list.
 * @param data A pointer to the main game data struct to populate.
 */
static void	convert_list_to_grid(t_list *head, t_data *data)
{
	t_list	*current;
	int		i;
	int		line_len;

	data->map.grid = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.grid)
		ft_print_error("Memory allocation failed for map grid.");
	current = head;
	i = 0;
	while (current)
	{
		line_len = ft_strlen((char *)current->content);
		if (((char *)current->content)[line_len - 1] == '\n')
			line_len--;
		if (line_len != data->map.size.x)
			ft_print_error("Map is not rectangular.");
		data->map.grid[i] = ft_substr((char *)current->content, 0, line_len);
		if (!data->map.grid[i])
			ft_print_error("Memory allocation failed for map line.");
		current = current->next;
		i++;
	}
	data->map.grid[i] = NULL;
}

/**
 * @brief Main entry point for the map parsing module.
 * 
 * This function orchestrates the entire map reading and validation process.
 * 
 * @param filename The path to the .ber map file
 * @param data A pointer to the main game data struct.
 * 
 */
void	parse_map(char *filename, t_data *data)
{
	int		fd;
	t_list	*map_list_head;

	map_list_head = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map file");
		exit(1);
	}
	read_map_to_list(fd, &map_list_head, data);
	close(fd);
	convert_list_to_grid(map_list_head, data);
	ft_lstclear(&map_list_head, free);
	validate_map_content(data);
	validate_path(data);
	ft_printf("[CHECK] Map is fully valid!\n");
}
