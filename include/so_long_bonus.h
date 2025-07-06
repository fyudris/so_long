/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:11:24 by fyudris           #+#    #+#             */
/*   Updated: 2025/07/07 01:04:02 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */
# include <mlx.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

/* ========================================================================== */
/* CONSTANTS                                                                  */
/* ========================================================================== */
// --- Game Style & Sizing ---
# define FRAME_DURATION 16666 // Time per frame in microseconds for ~60 FPS
# define ANIM_FRAME_DURATION 80000 // Time per anim frame in microsec. (~12 FPS)
# define ANIMATION_SPEED 10
# define ORIGINAL_TILE_SIZE 25
# define SCALE_FACTOR 2.0
# define TILE_SIZE 50
# define UI_HEIGHT 60
# define BABA_WALK_FRAMES 12

// --- Asset Paths ---
# define BABA_PATH "./assets/characters/Baba.xpm"
# define DOOR_PATH "./assets/statics/Door.xpm"
# define KEY_PATH "./assets/statics/Key.xpm"
# define FORT_PATH "./assets/tiles/Fort.xpm"
# define ROCK_PATH "./assets/statics/Rock.xpm"
# define FONT_PATH "./assets/texts/Font.xpm"
# define IS_PATH "./assets/texts/Is-Text.xpm"
# define MOVE_PATH "./assets/texts/Move-Text.xpm"
# define OPEN_PATH "./assets/texts/Open-Text.xpm"
# define PUSH_PATH "./assets/texts/Push-Text.xpm"
# define WIN_PATH "./assets/texts/Win-Text.xpm"
# define YOU_PATH "./assets/texts/You-Text.xpm"
# define WALL_PATH "./assets/tiles/Wall.xpm"

// --- Keycodes for Linux X11 ---
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

/* ========================================================================== */
/* DATA STRUCTURES                                                            */
/* ========================================================================== */

/**
 * @enum e_direction
 * @brief Represents the four cardinal directions the player can face.
 */
typedef enum e_direction
{
	DOWN,
	UP,
	LEFT,
	RIGHT
}	t_direction;

/**
 * @struct s_vector
 * @brief A generic structure to hold 2D integer coordinates (x, y).
 */
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/**
 * @struct s_img
 * @brief Represents an MLX image, holding its pointer and pixel data.
 */
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

/**
 * @struct s_map
 * @brief Holds all data related to the game map.
 */
typedef struct s_map
{
	char		**grid;
	t_vector	size;
	int			collectibles;
	int			players;
	int			exits;
}	t_map;

/**
 * @struct s_animation
 * @brief Represents a sequence of image frames for an animation.
 */
typedef struct s_animation
{
	t_img	*frames;
	int		frame_count;
}	t_animation;

/**
 * @struct s_anim_info
 * @brief A struct to pass animation loading parameters, keeping functions
 * compliant with the 4-argument Norm limit.
 */
typedef struct s_anim_info
{
	char		*path;
	int			frame_count;
	t_vector	start_pos;
}	t_anim_info;

/**
 * @struct s_game_rules
 * @brief Holds the boolean state for dynamic game rules from text blocks.
 */
typedef struct s_game_rules
{
	bool	key_is_activated;
	bool	wall_is_pushable;
	bool	rock_is_pushable;
}	t_game_rules;

/**
 * @struct s_textures
 * @brief A container for all game textures for the bonus version.
 */
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

/**
 * @struct s_data
 * @brief The main game data structure for the bonus version.
 */
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
	t_game_rules	rules;
	bool			is_moving;
	long			last_time;
	long			last_anim_time;
}	t_data;

/* ========================================================================== */
/* FUNCTION PROTOTYPES                                                        */
/* ========================================================================== */

// --- Core Game Functions ---
void			init_game_data(t_data *data);
void			init_mlx(t_data *data);
void			parse_map(char *filename, t_data *data);
void			validate_map_content(t_data *data);
void			validate_path(t_data *data);
int				render_frame(t_data *data);
void			load_all_textures(t_data *data);
void			cleanup_and_exit(t_data *data, int status);

// --- Event Hook Functions ---
int				handle_close_window(t_data *data);
int				handle_keypress(int keycode, t_data *data);
int				handle_keyrelease(int keycode, t_data *data);

// --- Image & Pixel Utilities ---
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			put_pixel_to_img(t_img *img, int x, int y, unsigned int color);
void			unpack_sprite(t_img *dest, t_img *src, t_vector pos);
void			upscale_sprite(t_img *dest, t_img *src);
void			draw_sprite_to_buffer(t_img *buffer, t_img *sprite,
					t_vector pos);
void			clear_image_buffer(t_img *img, int color);

// --- Bonus Logic Functions ---
bool			handle_push(t_data *data, t_vector obj_pos);
void			update_game_rules(t_data *data);
bool			is_pushable(t_data *data, char tile);

// --- Texture Loading Utilities ---
void			process_one_frame(t_data *data, t_img *final_img, t_img *sheet,
					t_vector pos);
void			load_animation(t_data *data, t_animation *anim,
					t_anim_info info);
void			load_baba_animation(t_data *data, t_animation *anim,
					char *path, int start_col);

// --- Hooks & UI Utilities ---
void			update_player_direction(int keycode, t_data *data);
bool			check_collisions(t_data *data, t_vector next_pos);
bool			process_interactions(t_data *data, t_vector next_pos);
void			finalize_move(t_data *data, t_vector next_pos);
long			get_time_in_usec(void);
void			draw_ui_left(t_data *data);
void			draw_ui_right(t_data *data);
void			draw_number(t_data *data, int n, t_vector pos);
t_animation		*get_object_anim(t_data *data, char tile_type);
#endif
