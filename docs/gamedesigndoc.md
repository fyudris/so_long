# Game Design Document


### Legends
| Character | so_long Component | Your Game's Object | Description                                               |
|-----------|-------------------|--------------------|-----------------------------------------------------------|
| 1         | Wall              | Fort               | The mandatory, unpenetrable enclosing wall.              |
| 0         | Empty Space       | Empty Space        | A walkable tile.                                         |
| P         | Player Start      | Baba               | The player's starting position.                          |
| p         | Text Block        | "BABA" Text        | Pushable text block. Can be static (in a rule box).      |
| C         | Collectible       | Key (The Item)     | The mandatory item that must be collected to enable the exit. |
| c         | Text Block        | "KEY" Text         | Pushable text block.                                     |
| E         | Custom Obstacle   | Door (Obstacle/The Exit)    | A temporary barrier that can be opened by a rule. The final tile to step on to win the game.         |
| e         | Text Block        | "DOOR" Text        | Pushable text block. Can be static or part of a puzzle.  |
| W         | Custom Obstacle   | Wall (Obstacle)    | An interactive obstacle whose properties can be changed. |
| w         | Text Block        | "WALL" Text        | Pushable text block.                                     |
| R         | Custom Obstacle   | Rock (Obstacle)    | An interactive obstacle.                                 |
| r         | Text Block        | "ROCK" Text        | Pushable text block.                                     |
| y         | Text Block        | "YOU" Text         | Pushable text block. Can be static.                      |
| n         | Text Block        | "WIN" Text         | Pushable text block. Can be static.                      |
| i         | Text Block        | "IS" Text          | Pushable text block.                                     |
| o         | Text Block        | "OPEN" Text        | Pushable text block.                                     |
| u         | Text Block        | "PUSH" Text        | Pushable text block.                                     |

Frame-Rate Dependent Animation
The Workload: Your current render_frame function uses a loop to draw every single tile of the map, one by one, in every single frame.

A small 10x10 map requires ~100 draw calls per frame.
A large 50x50 map requires ~2500 draw calls per frame.
The Frame Rate (FPS): The more work your program has to do to draw a single frame, the longer it takes.

Small Map: Less work per frame -> frames are drawn very quickly -> High FPS (e.g., 200 frames per second).
Large Map: More work per frame -> frames are drawn slowly -> Low FPS (e.g., 30 frames per second).
The Animation Timer: Your animation logic is currently frame-based.

C

data->anim_timer++;
if (data->anim_timer >= ANIMATION_SPEED)
{
    data->anim_timer = 0;
    data->anim_frame++;
}
This code says, "after ANIMATION_SPEED number of frames have passed, advance the animation." It doesn't know anything about real-world time.

This is why you see the speed difference:

On a small map with high FPS, the anim_timer counts up to ANIMATION_SPEED very quickly, causing the animation to look fast.
On a large map with low FPS, the anim_timer counts up much more slowly, causing the animation to look sluggish.
The Solution: The Background Buffer Technique
The professional solution in major game engines is to use "delta time" to make animations time-based, not frame-based. However, this is difficult to implement reliably in so_long as MiniLibX doesn't provide a high-precision timer.

The best and most common solution for this project is to drastically reduce the work done per frame by pre-rendering your static map onto a single background image.

The Strategy:

On Startup: After parsing the map, create one large image buffer the size of the entire window.
Draw the entire static map (forts, walls, floors, non-animating objects) onto this buffer just once.
In the Game Loop: Instead of drawing hundreds of tiles every frame, you just draw the single, pre-rendered background image, and then draw your few dynamic objects (like the player and shimmering keys) on top.
This completely decouples the rendering performance from the map size.

Step 1: Update Your Data Structures (so_long.h)
Add a new t_img to your main data struct to hold the pre-rendered background.

C

// In t_data struct
typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		background; // <-- ADD THIS
	// ... rest of your struct ...
}	t_data;
Step 2: Create a New Prerendering Function
Create a new function that will be called only once from main.c, right after load_all_textures.

In srcs/rendering/render.c (or a new srcs/rendering/background.c):

C

/**
 * @brief Creates a single background image and pre-renders all static
 * map elements onto it. This is done only once at startup.
 */
void	prerender_background(t_data *data)
{
	int	x;
	int	y;

	// Create a new blank image the size of the window
	data->background.ptr = mlx_new_image(data->mlx,
			data->map.size.x * TILE_SIZE, data->map.size.y * TILE_SIZE);
	if (!data->background.ptr)
		ft_print_error("Failed to create background buffer.");
	data->background.addr = mlx_get_data_addr(data->background.ptr,
			&data->background.bpp, &data->background.line_len,
			&data->background.endian);
	
	// Loop through the map and draw every STATIC tile onto the buffer
	y = -1;
	while (++y < data->map.size.y)
	{
		x = -1;
		while (++x < data->map.size.x)
		{
			char tile_type = data->map.grid[y][x];
			// We only draw static, non-animated things here.
			// '1' (Fort) and '0' (Floor/Empty) are good candidates.
			if (tile_type == '1')
				unpack_sprite(&data->background, &data->textures.fort_wall.frames[0], (t_vector){x * TILE_SIZE, y * TILE_SIZE});
			// You could also draw a floor tile here for '0' if you had one.
		}
	}
}
Note: This version of prerender_background uses unpack_sprite to copy pixels directly to the background buffer. You would need to modify unpack_sprite slightly to take the destination (x, y) as a parameter.

Step 3: Update Your render_frame Function
Your main render loop now becomes incredibly fast and simple.

In srcs/rendering/render.c:

C

int	render_frame(t_data *data)
{
	// ... (Your animation timer logic remains the same) ...

	// 1. Draw the entire pre-rendered background in ONE call.
	mlx_put_image_to_window(data->mlx, data->win, data->background.ptr, 0, 0);

	// 2. Loop and draw ONLY your DYNAMIC objects on top.
	//    (e.g., collectibles, enemies, and interactive objects)
	//    This replaces your old map-drawing loop.
	//    ... (draw_dynamic_tiles loop) ...

	// 3. Draw the player on top of everything.
	// ... (your player drawing logic remains the same) ...
	
	return (0);
}