# QtGameOfLife
Conway's Game of Life in Qt

----------
How to Use
----------

Display config
--------------
The display config box allows the user to configure the display window.
The "Borders connected" box determines if the borders of the game map are connected. When it is checked, it means that the left and right edges of the field are stitched together and the top and bottom are also, creating a toroidal space. Currently, this is the only mode that's working properly so this box should be left checked.
The "Square size" field determines the size in pixels of one square of the field.
The "Update" button allows the user to apply the changes made to the display configuration.

The "Next" button
-----------------
The "Next" button executes one step of the game of life. The display window shall immediately reflect the new state of the game.

The "Play/Pause" button
-----------------------
When pressed, this button shall start the continuous execution of the game, performing around 10 steps per second. When pressed again, the execution shall stop.

The "Load pattern" button
-------------------------
When this button is pressed, a window appears, asking the user to choose a file to use as a starting pattern for the game.

-------------------
Pattern file format
-------------------
The patterns are contained in plain .txt files.
The first line of the file shall indicate the size of the field by specifying the height and width separated by a space (ex: "50 70" means a field of 50 units in height and 70 units in width).
Each following line shall specify the coordinates in the field of one cell of the pattern.
