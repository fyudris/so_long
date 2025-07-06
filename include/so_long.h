/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:44:57 by fyudris           #+#    #+#             */
/*   Updated: 2025/07/07 01:04:01 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */
# include <mlx.h>           // Core MiniLibX library for graphics
# include <stdbool.h>       // For using bool, true, and false
# include <stdlib.h>        // For malloc, free, and exit
# include <fcntl.h>         // For open() file control options
# include <unistd.h>        // For read, write, and close
# include <sys/time.h>      // For gettimeofday() to manage frame timing
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"

/* ========================================================================== */
/* CONSTANTS                                                                  */
/* ========================================================================== */

// --- Game Style & Sizing ---

/** @def FRAME_DURATION
 * @brief The minimum time in microseconds for one frame (~60 FPS).
 */
# define FRAME_DURATION 16666
/** @def ORIGINAL_TILE_SIZE
 * @brief The width and height of a single sprite in the source .xpm files.
 */
# define ORIGINAL_TILE_SIZE 25
/** @def SCALE_FACTOR
 * @brief The multiplier to scale up sprites for the final display.
 */
# define SCALE_FACTOR 2.0
/** @def TILE_SIZE
 * @brief The final on-screen size of a tile after scaling.
 */
# define TILE_SIZE 50
/** @def ANIMATION_SPEED
 * @brief Controls the speed of sprite animations. Lower is faster.
 */
# define ANIMATION_SPEED 20

// --- Asset Paths ---
# define BABA_PATH "./assets/characters/Baba.xpm"
# define DOOR_PATH "./assets/statics/Door.xpm"
# define KEY_PATH "./assets/statics/Key.xpm"
# define FORT_PATH "./assets/tiles/Fort.xpm"

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
 * @param ptr Pointer to the image resource, used by MLX functions.
 * @param addr Pointer to the raw pixel data buffer.
 * @param width Width of the image in pixels.
 * @param height Height of the image in pixels.
 * @param bpp Bits per pixel.
 * @param line_len The number of bytes in one horizontal line of the image.
 * @param endian The endianness of the image data.
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
 * @param grid A 2D char array representing the map layout.
 * @param size The dimensions (width and height) of the map in tiles.
 * @param collectibles The total number of collectibles ('C') on the map.
 * @param players The count of player start positions ('P').
 * @param exits The count of map exits ('E').
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
 * @param frames A dynamically allocated array of `t_img` structs.
 * @param frame_count The total number of frames in the animation.
 */
typedef struct s_animation
{
	t_img	*frames;
	int		frame_count;
}	t_animation;

/**
 * @struct s_textures
 * @brief A container for all mandatory game textures.
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
}	t_textures;

/**
 * @struct s_data
 * @brief The main game data structure, passed to all major functions.
 * @details This "god struct" holds pointers to all essential game components,
 * including the MLX instance, the window, the map data, player state,
 * and all loaded textures.
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
	int				anim_timer;
	long			last_time;
}	t_data;

/* ========================================================================== */
/* FUNCTION PROTOTYPES                                                        */
/* ========================================================================== */

// --- Initialization ---
void			init_game_data(t_data *data);
void			init_mlx(t_data *data);

// --- Map Parsing & Validation ---
void			parse_map(char *filename, t_data *data);
void			validate_map_content(t_data *data);
void			validate_path(t_data *data);

// --- Rendering & Textures ---
int				render_frame(t_data *data);
void			load_all_textures(t_data *data);

// --- Cleanup ---
void			cleanup_and_exit(t_data *data, int status);

// --- Event Hooks ---
int				handle_close_window(t_data *data);
int				handle_keypress(int keycode, t_data *data);

// --- Image Utilities ---
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			put_pixel_to_img(t_img *img, int x, int y, unsigned int color);
void			unpack_sprite(t_img *dest, t_img *src, t_vector pos);
void			upscale_sprite(t_img *dest, t_img *src);
void			draw_sprite_to_buffer(t_img *buffer, t_img *sprite,
					t_vector pos);
void			clear_image_buffer(t_img *img, int color);

// --- Time Utilities ---
long			get_time_in_usec(void);

#endif
