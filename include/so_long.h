/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:44:57 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/18 14:56:31 by fyudris          ###   ########.fr       */
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

// # define TILE_SIZE 24
# define ORIGINAL_TILE_SIZE 25
# define SCALE_FACTOR 3
# define TILE_SIZE (ORIGINAL_TILE_SIZE * SCALE_FACTOR) // e.g., 48
# define ANIMATION_FRAMES 4 // 4 frames per direction 
# define BABA_WALK_FRAMES 12
# define ANIMATION_SPEED 125 // higher number = slower animation

/* ----- Assets Path ----- */
# define BABA_PATH "./assets/characters/Baba.xpm"
# define DOOR_PATH "./assets/statics/Door.xpm"
# define KEY_PATH "./assets/statics/Key.xpm"
# define ROCK_PATH "./assets/statics/Rock.xpm"
# define FONT_PATH "./assets/texts/Font.xpm"
# define IS_PATH "./assets/texts/Is-Text.xpm"
# define LEVEL_PATH "./assets/texts/Level-Text.xpm"
# define MOVE_PATH "./assets/texts/Move-Text.xpm"
# define OPEN_PATH "./assets/texts/Open-Text.xpm"
# define PUSH_PATH "./assets/texts/Push-Text.xpm"
# define WIN_PATH "./assets/texts/Win-Text.xpm"
# define YOU_PATH "./assets/texts/You-Text.xpm"
# define FORT_PATH "./assets/tiles/Fort.xpm"
# define WALL_PATH "./assets/tiles/Wall.xpm"

/* ----- Keycodes for Linux X11 ----- */

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

/* ----- Player Direction ----- */
typedef enum	e_direction
{
	DOWN,
	UP,
	LEFT,
	RIGHT
} t_direction;

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
	void	*addr; // Pointer to the raw pixel data buffer
	int		width;
	int		height;
	int		bpp; // Bits per pixel
	int		line_len; // The number of bytes in one horizon
	int		endian; // The endianess of the image data
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

typedef struct	s_animation
{
	t_img	*frames;
	int		frame_count;
}	t_animation;

// Hold game textures
typedef struct s_textures
{
	t_animation	player_down;
	t_animation	player_up;
	t_animation	player_left;
	t_animation	player_right;
	t_animation	player_txt;
	t_animation	wall;
	t_animation	wall_txt;
	t_animation	fort_wall;
	// t_animation	fort_wall_txt;
	t_animation	key;
	t_animation	key_txt;
	t_animation	door;
	t_animation	door_txt;
	t_animation	you_txt;
	t_animation	open_txt;
	t_animation	push_txt;
	t_animation	win_txt;
	t_animation	is_txt;
}	t_textures;

// Main game data struct, passed to all function
typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_vector		player_pos;
	int				move_count;
	bool			player_has_key;
	t_game_rules	rules;
	t_textures		textures;
	t_direction		player_dir;
	int				anim_frame;
	int				anim_timer;
	bool			is_moving;
}	t_data;

/* ----- Function Prototypes ----- */

// init.c
void	init_game_data(t_data *data);
void	init_mlx(t_data *data);

// Map Parsing
void	parse_map(char *filename, t_data *data);

// Map Validation
void	validate_map_content(t_data *data);

// Path Validation
void	validate_path(t_data *data);

// Rendering
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			put_pixel_to_img(t_img *img, int x, int y, unsigned int color);
void			upscale_sprite(t_img *dest, t_img *src);
int				render_frame(t_data *data);
void			load_all_textures(t_data *data);
// void			load_animation(t_data *data, t_animation *anim, char *path,
// 				int frame_count, t_vector start_pos);
void	unpack_sprite(t_img *dest, t_img *src, t_vector pos);

// Game
int	handle_close_window(t_data *data);
int	handle_keyrelease(int keycode, t_data *data);
int	handle_keypress(int keycode, t_data *data);


// Memory
void	cleanup_and_exit(t_data *data, int status);

#endif