/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:44:57 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/24 20:18:25 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/

# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/*============================================================================*/
/* CONSTANTS                                                                  */
/*============================================================================*/

// --- Game Style & Sizing ---
# define ORIGINAL_TILE_SIZE 25
# define SCALE_FACTOR 2.0
# define TILE_SIZE 50
# define ANIMATION_SPEED 25

// --- UI & Bonus Constants ---
# ifdef BONUS_PART
#  define UI_HEIGHT 60
#  define BABA_WALK_FRAMES 12
# endif

// --- Asset Paths ---
# define BABA_PATH "./assets/characters/Baba.xpm"
# define DOOR_PATH "./assets/statics/Door.xpm"
# define KEY_PATH "./assets/statics/Key.xpm"
# define FORT_PATH "./assets/tiles/Fort.xpm"
# ifdef BONUS_PART
#  define ROCK_PATH "./assets/statics/Rock.xpm"
#  define FONT_PATH "./assets/texts/Font.xpm"
#  define IS_PATH "./assets/texts/Is-Text.xpm"
#  define MOVE_PATH "./assets/texts/Move-Text.xpm"
#  define OPEN_PATH "./assets/texts/Open-Text.xpm"
#  define PUSH_PATH "./assets/texts/Push-Text.xpm"
#  define WIN_PATH "./assets/texts/Win-Text.xpm"
#  define YOU_PATH "./assets/texts/You-Text.xpm"
#  define WALL_PATH "./assets/tiles/Wall.xpm"
# endif

// --- Keycodes for Linux X11 ---
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

/*============================================================================*/
/* DATA STRUCTURES                                                            */
/*============================================================================*/

typedef enum e_direction
{
	DOWN,
	UP,
	LEFT,
	RIGHT
}	t_direction;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char		**grid;
	t_vector	size;
	int			collectibles;
	int			players;
	int			exits;
}	t_map;

typedef struct s_animation
{
	t_img	*frames;
	int		frame_count;
}	t_animation;

# ifdef BONUS_PART
// --- Bonus Version of Structs ---

typedef struct s_game_rules
{
	bool	key_is_activated;
	bool	wall_is_pushable;
	bool	rock_is_pushable;
}	t_game_rules;

typedef struct s_textures
{
	t_animation	player_down;
	t_animation	player_up;
	t_animation	player_left;
	t_animation	player_right;
	t_animation	key;
	t_animation	door;
	t_animation	fort_wall;
	t_animation	player_txt;
	t_animation	wall;
	t_animation	wall_txt;
	t_animation	key_txt;
	t_animation	door_txt;
	t_animation	rock;
	t_animation	rock_txt;
	t_animation	you_txt;
	t_animation	open_txt;
	t_animation	push_txt;
	t_animation	win_txt;
	t_animation	is_txt;
	t_animation	ui_move_icon;
	t_animation	ui_key_icon;
	t_animation	ui_x_icon;
	t_animation	ui_digits[10];
	t_vector	digit_coords[10];
}	t_textures;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			game_buffer;
	t_map			map;
	t_vector		player_pos;
	int				move_count;
	int				keys_collected;
	t_textures		textures;
	t_direction		player_dir;
	int				anim_frame;
	int				anim_timer;
	t_game_rules	rules;
	bool			is_moving;
}	t_data;

# else
// --- Mandatory Version of Structs ---

typedef struct s_textures
{
	t_animation	player_down;
	t_animation	player_up;
	t_animation	player_left;
	t_animation	player_right;
	t_animation	key;
	t_animation	door;
	t_animation	fort_wall;
}	t_textures;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			game_buffer;
	t_map			map;
	t_vector		player_pos;
	int				move_count;
	int				keys_collected;
	t_textures		textures;
	t_direction		player_dir;
	int				anim_frame;
	int				anim_timer;
}	t_data;

# endif

/*============================================================================*/
/* FUNCTION PROTOTYPES                                                        */
/*============================================================================*/

// --- Shared Functions ---
void			init_game_data(t_data *data);
void			init_mlx(t_data *data);
void			parse_map(char *filename, t_data *data);
void			validate_map_content(t_data *data);
void			validate_path(t_data *data);
int				render_frame(t_data *data);
void			load_all_textures(t_data *data);
void			cleanup_and_exit(t_data *data, int status);
int				handle_close_window(t_data *data);
int				handle_keypress(int keycode, t_data *data);

// Image utils
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			put_pixel_to_img(t_img *img, int x, int y, unsigned int color);
void			unpack_sprite(t_img *dest, t_img *src, t_vector pos);
void			upscale_sprite(t_img *dest, t_img *src);
void			draw_sprite_to_buffer(t_img *buffer, t_img *sprite,
					t_vector pos);
void			clear_image_buffer(t_img *img, int color);

// --- Bonus-Only Functions ---
# ifdef BONUS_PART

int				handle_keyrelease(int keycode, t_data *data);
bool			handle_push(t_data *data, t_vector obj_pos);
void			update_game_rules(t_data *data);
# endif

#endif
