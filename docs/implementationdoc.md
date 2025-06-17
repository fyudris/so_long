# Implementations

## Step 1: Read the Map File & Check Geometry
The Goal: Open the file specified by the command-line argument, read its contents, and validate that it is a rectangle.

The Plan:

- Read line by line: The best tool for this is get_next_line from your libft. Read the file once to determine its height and to check if all lines have the same width. A robust way to do this is to read the lines into a temporary linked list (t_list).
- Validate Rectangular Shape:
Read the first line and store its length as the official width.
For every subsequent line, compare its length to the stored width. If any line differs, the map is not rectangular, and you must exit with an error.
- Store Dimensions: Once validated, store the final width and height in your data->map.size struct.
- Convert to Grid: Allocate memory for data.map.grid (char **) using the now-known width and height. Iterate through your temporary linked list and copy each line into the grid. Free the linked list.

### How to Test This Step:

In your main.c, temporarily add a for loop after calling parse_map that prints the contents of data->map.grid to the terminal.
Create a maps/valid_rect.ber file. Run ./so_long maps/valid_rect.ber. The output in your terminal should exactly match the file.
Create a maps/invalid_rect.ber where the lines have different lengths. Your program should exit cleanly and print an error message like "Error\nMap is not rectangular."

Excellent. Your project is fully set up, and you're ready to start coding the first major feature.


## Step 2: Validate Map Content & Components

### The Goal: Now that the map is in memory, check its contents against the project rules. This can be one or more functions called from your main parse_map function.

### The Plan:

- Check for Wall Enclosure: Iterate through the border of your data.map.grid. The entire first and last row, and the first and last column of every row, must be a '1' (your Fort). If not, it's an error.

- Count Components & Check Characters:
Iterate through the entire grid (ignoring the border you just checked).
Use counters (data.map.players, data.map.exits, data.map.collectibles) to count every 'P', 'E', and 'C'.
While iterating, if you encounter any character that is not part of your allowed set (0, 1, P, C, E, and your custom object/text characters), it's an error.
After iterating, check if the component counts are correct: exactly 1 Player, exactly 1 Exit, and at least 1 Collectible.

#### How to Test This Step:

Create a maps/error_wall.ber with a gap in the surrounding wall. Your program should exit with an error.
Create a maps/error_char.ber with an invalid character like 'X'. Your program should exit with an error.
Create several maps/error_components.ber files: one with two 'P's, one with no 'E', one with no 'C'. Each should cause a specific error exit.
Step 3: The Final Check - Path Validation
The Goal: Verify that there is a valid path from the player's start to all collectibles and to the exit.

The Plan:
This is the most complex validation step. The standard algorithm for this is Flood Fill.

Create a Copy: Make a deep copy of data.map.grid. You cannot modify the original map.
Find Start: Get the player's starting coordinates (x, y) that you stored when you counted the components.
Implement Flood Fill: Create a recursive function, for example flood_fill(char **map_copy, int x, int y).
This function "fills" the current tile (e.g., changes it to an 'F' for "filled").
It then recursively calls itself for the four adjacent tiles (up, down, left, right), but only if that tile is not a wall ('1') and has not already been filled.
Check Reachability: After the flood fill recursion is complete, iterate through your original map grid. For every 'C' and 'E', check the corresponding coordinate in your copied, filled map.
If any 'C' or 'E' position in the copy is not an 'F', it means the flood fill could not reach it. This is a pathing error, and the program must exit.
How to Test This Step:

Create a maps/error_path.ber where a 'C' or the 'E' is completely walled off from the player. Your program must detect this and exit with a "No valid path" error.
Run your program on your valid level1.ber and level2_spacious.ber. It should pass all validation steps without error.
Once your parse_map function can successfully validate all these conditions, your project's foundation will be incredibly solid. You'll be ready to move on to the fun part: initializing MiniLibX and rendering your validated map.
