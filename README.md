# so_long

## Subject
- Turn in files: Makefile, *.h, *.c, maps
- Arguments: A map in format *.ber
- External functions:
  - open, close, read, write, malloc, free, perror, strerror, exit
  - All functions of the math library (-lm compiler option, man man 3 math)
  - All functions of the MiniLibX
  - ft_printf and any equivalent YOU coded
- Libft is authorized
- Description:
	...
- Rules
  - You must use the MiniLibX.
  - You have to turn in a Makefile (no relink).
  - Your program has to take a map description file ending with the `.ber` extension as parameter.

### 1. Game
- Player's Goal: Collect every collectible present on the map, then escape chosing the shortest possible route.
- `W`, `A`, `S`, and `D` keys must be used to move the main character.
  ```
  If you prefer, you can use ZQSD or the arrow keys on your keyboard to move your main character.
  ```
- The player should be able to move in 4 direcitons: **up, down, left, and right**.
- The player should not be able to move into walls.
- At every move, the current **number of movements** must be displayed in the shell.
- You have to use a **2D view** (top-down or profile).
- The game doesn't have to be real time.
- Any world/theme is permited.

### 2. Graphic Management
- Your program has to display the image in a window.
- The management of your windo must remain smooth (changing to another window, minimizing, etc.).
- Pressing `ESC` must close the window and quit the program in a clean way.
- Clicking ont he cross on the window's frame must close the window and quit the program a clean way.
- The use of the `images` of the `MiniibX` is mandatory.

### 3. Map
- The map has to be constructed with 3 components: **walls, collectibles, and free space**.
- The map can be composed of only these 5 characters:
	```
	0	-	for an empty space
	1	-	for a wall
	C	-	for a collectible
	E	-	for a map exit
	P	-	for the player's starting possition
	```
	Here is a simple valid map:
	```
	1111111111111
	10010000000C1
	1000011111001
	1P0011E000001
	1111111111111
	```
- The map must contain at least **1 exit, 1 collectible**, and **1 starting position**
	```
	If the map contains a duplicated characters (exit/start), you should display an error message.
	```
- The map must be rectangular.
- The map must be closed/surrounded by walls. If not, the program must return an error.
- You have to check if there's a valid path in the map.
- You must be able to parse any kind of map, as long as it respects the above rules.

  Another example a minial .ber map:
  ```
	1111111111111111111111111111111111
	1E0000000000000C00000C000000000001
	1010010100100000101001000000010101
	1010010010101010001001000000010101
	1P0000000C00C0000000000000000000C1
	1111111111111111111111111111111111
  ```
-  If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way, and return `Error\n` followed by an explicit error message of your choice.

### 4. Bonus
You will get extra points if you:
- Make the player lose when they touch an enemy patrol.
- Add some sprite animation.
- Display they movement count directly on screen instead of writting it in the shell.

---

## Project Configuration

### MLX Library

#### 1. Makefile Config
For object files, you could add the following rule to your makefile, assuming that you have the mlx for linux source in a directory named mlx_linux in the root of your project:
```
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

```
To link with the required internal Linux API:
```
$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
```

#### 2. Initialization
Before we can do anything with the MiniLibX library we must include the `<mlx.h>` header to access all the functions and we should execute the `mlx_init` function. This will establish a connection to the correct graphical system and will return a `void *` which holds the location of our current MLX instance. To initialize MiniLibX one could do the following:
```
#include <mlx.h>

int	main(void)
{
	void	*mlx;

	mlx = mlx_init();
}
```

### Understanding MLX
Now that your project is compiling, let's get you started with the fun part: actually using MiniLibX to put things on the screen.
We'll go through the essentials step-by-step:
1. Initialize the Library & Create a Window
2. Handle Events (like closing the window)
3. Draw Pixels and Images
4. Put it all together in a simple starting program

#### Step 1: The Bare Minimum - Creating a Window
Every MiniLibX program starts with three essential steps:
1. `mlx_init()`: Establish a connection to the graphical server. This is always the first thing you must call.
2. `mlx_new_window()`: Create an on-screen window.
3. `mlx_loop()`: Start the event loop. This function listens for events (like key presses or mouse clicks) and will not return. Your program will stay running in this loop until you close the window.

Let's write this in your `srcs/main.c`.
```
#include "so_long.h"
#include <mlx.h> // The core MiniLibX header

// Define some constants for window size
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 
```

// We need a structure to hold our mlx pointers
```
typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	main(void)
{
	t_data	data;

	// 1. Initialize the library
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1); // Error
	
	// 2. Create the window
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My First Window!");
	if (data.win_ptr == NULL)
		return (1);
	
	// 3. Start the event loop
	mlx_loop(data.mlx_ptr);

	// The program will not reach here until the window is closed.
	return (0);
}
```

#### Step 2: Handling Events - Closing the Window
To make the window interactive, you need to register "callback" functions that MiniLibX will call when something happens. This is done with `mlx_hook()` or its simpler variants like `mlx_key_hook()`.

An "event" is any user action: pressing a key, moving the mouse, clicking a button, or even trying to close the window.

We need a function that closes the window and a way to tell MiniLibX "Call this function when the ESC key is pressed".

```
#include "so_long.h"
#include <mlx.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define KEY_ESC 65307

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

/**
 * @brief This function is called when a key is pressed.
 *
 * @param keycode The code of the key that was pressed.
 * @param data A pointer to our custom data structure.
 * @return int Always return 0.
 */
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL; // Good practice
		exit(0); // Simple way to exit the program
	}
	return (0);
}

/**
 * @brief This function is called when the red 'X' is clicked.
 */
int	handle_close_button(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	exit(0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Closable Window");
	if (!data->win_ptr)
		return (1);

	// --- NEW STUFF HERE ---
	// Register the keypress handler
	// mlx_key_hook is a simpler version of mlx_hook for key presses.
	mlx_key_hook(data->win_ptr, handle_keypress, &data);

	// Register the close button handler
	// The event code '17' corresponds to the 'DestroyNotify' event.
	// The mask '0' means no specific event mask.
	mlx_hoo(data->win_ptr, 17, 0, handle_close_button, &data);

	mlx_loop(datta->mlx_ptr);

	return (0);
}
```

