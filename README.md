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
