# GIMP Commands

## Selecting From Sprites Sheet

1. Open your image in GIMP
```
File > open
```
2. Use the rectange select tool
```
From the Toolbox (left side of the screen) > Rectangle Select Tool
Click and drag a box around the desired characters
```
3.  Enable Snap to Grid
```
View > Check Snap to Grid

Image > Configure Grid (e.g. 24 x 24 pixel grid)
```
Drag the corners of your selection box to snap into grid lines.
4.  Crop your selection
```
Image > Crop to selection
```
5. Export

## Remove Background from the Character
1. Add an Alpha Channel
   ```
   In Layers panel (right-hand side of the screen), right click on your image layer > Select Add Alpha Channel

   In the Tool Option > Fuzzy Select Tool > Set Threshold to low value e.g. 15

   Click anywhere on the background of the image to remove matching colors > Delete
   ```

2. 