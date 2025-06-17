/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:44:57 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 14:15:02 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ----- Includes ----- */

# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

/* ----- Game Constants ----- */

# define TILE_SIZE 32

/* ----- Keycodes for Linux X11 ----- */

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

/* ----- Data Structures ----- */

// 2D coordinates
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

// Image/texture data
typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
}	t_img;

// Map data
typedef struct s_map
{
	char		**grid;
	t_vector	size;
	int			collectibles;
	int			players;
	int			exits;
}	t_map;

// Manage the state of game rules
typedef struct s_game_rules
{
	bool	key_is_activated;
	bool	wall_is_pushable;
}	t_game_rules;

// Hold game textures
typedef struct s_textures
{
	t_img	player;
	t_img	player_txt;
	t_img	wall;
	t_img	wall_txt;
	t_img	fort_wall;
	t_img	fort_wall_txt;
	t_img	key;
	t_img	key_txt;
	t_img	door;
	t_img	door_txt;
	t_img	you_txt;
	t_img	open_txt;
	t_img	push_txt;
	t_img	win_txt;
	t_img	is_txt;
}	t_textures;

// Main game data struct, passed to all function
typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_vector		player_pos;
	int				move_count;
	bool			keys_collected;
	t_game_rules	rules;
	t_textures		textures;
}	t_data;

/* ----- Function Prototypes ----- */

// init.c
void	init_game_data(t_data *data);

// Map Parsing
void	parse_map(char *filename, t_data *data);

// Map Validation
void	validate_map_content(t_data *data);

// Path Validation
void	validate_path(t_data *data);

#endif