/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:54:15 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 18:30:36 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_map.c
 * @brief Functions for parsing and validating the .ber map file.
 *
 * @details This file orchestrates the process of reading a map file,
 * converting it from a file into a 2D array (grid), and then running
 * a series of validations to ensure it conforms to the project's rules.
 * It uses a temporary linked list to handle maps of unknown height before
 * allocating the final memory block for the grid.
 */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Reads the map from a file descriptor into a temporary linked list.
 *
 * @details This function reads the map file line by line using `get_next_line`.
 * It uses the first line to determine the required width of the map.
 *
 * @param fd The file descriptor for the open map file.
 * @param map_list_head A pointer to the head of the linked list.
 * @param data A pointer to the main game data struct, where the map's
 * dimensions (`size.x` and `size.y`) will be stored.
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
			data->map.size.x = ft_strlen(line);
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
 * @details It performs a crucial validation: it checks
 * if every line has the same length as the first one. If not, the map is
 * not rectangular, and the program exits with an error.
 *
 * @param head A pointer to the head of the linked list containing map lines.
 * @param data A pointer to the main game data struct. This function will
 * populate `data->map.grid`.
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
 * @details This function orchestrates the entire map reading and validation
 * process in the correct order:
 * 1. Opens the specified file.
 * 2. Reads the file content into a temporary linked list.
 * 3. Closes the file.
 * 4. Converts the linked list into the final `char **` grid.
 * 5. Frees the temporary linked list.
 * 6. Calls subsequent functions to validate the map's content (walls, items)
 * and ensure a valid path exists.
 *
 * @param filename The path to the `.ber` map file provided as a command-line
 * argument.
 * @param data A pointer to the main game data struct to be populated.
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
