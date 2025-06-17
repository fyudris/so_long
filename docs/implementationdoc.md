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
