# Tetris

This is one of my first experiences with SDL and C++ from back in the day when I was learning the language. I thought I'd upload it as a reminder of where I started.
Please do keep in mind this code is more than 8 years old.

_Game: Tetris, pieces fall, completing a line awards 10 points, and every 100 points increase the speed at which pieces fall (level up). Keys: left, right, and down for movement (arrows), to rotate use the up arrow (rotate right) and Z (rotate left)._

*Remember to compile the project in x86, as the .vs folder is not in the repository, memory usage may be higher than usual (around 60MB).*

**Tetris**

For this project, I decided to use the SDL2 library for input, sound, and graphics because I had already worked with it and had the setup on my computer, and I was familiar with its basic functions.

To begin with, I will have a class called "Tetromino." This class will be abstract and have three basic functions:

- Return a position
- Rotate to the right
- Rotate to the left

The pieces are defined in a 4x4 two-dimensional array, and each piece is a CHILD class of TETROMINO.

The two-dimensional array (for the pieces: cube, I, L, mirror L, N, mirror N, and T) will be filled with 0 representing empty spaces and 1 for blocks.

Example for T:

{0,0,0,0}

{0,0,1,0}

{0,0,1,1}

{0,0,1,0}

Rotated T:

{0,0,0,0}

{0,0,0,0}

{0,1,1,1}

{0,0,1,0}

To work with the relevant rotations, we store the rotation state in an enum. Each object will have the impressions of the different rotations stored in a 3-dimensional array (except for the cube or square because it has no rotations). The first dimension is the current rotation state, and the others are the position in the 4x4 array.

As for the board, we will have another class called "Board" that will:

- Have a 10x20 array of type char that starts with all positions as FREE. As each square is filled, their state changes. (The possible states are stored in an enum, which are FREE and OCCUPIED.)
- Contain a function that initializes the board (fills everything as FREE).
- Contain another function to SAVE pieces, i.e., change the state of the cubes to OCCUPIED, depending on the Tetromino (a Tetromino needs to be passed, but it only gives the value in a specific position to avoid being changed).
- A function that clears ONE LINE from the array as they are completely changed to OCCUPIED, and this can redraw the board by moving the pieces. Another function may act together to check how many lines need to be eliminated and call the clear ONE LINE function when necessary.
- A method to check if a block is empty or not to detect collisions later.
- We will also need get methods for the blocks, which simply return the value of the position. This is useful in case you want to change the color of the stored blocks or if the array stores values related to a sprite.
- A function that returns a boolean to let us know if the movement is possible or not, using the previous methods to check for collisions.

Two classes were created for the graphical implementation: Window and Rect. The first one creates the window, clears it, updates the screen, and takes input with SDL to close the game. It only manages the window and the initialization of SDL processes.

Rect, on the other hand, inherits the RENDERER from the window to avoid creating another one (only one renderer can be used per window), and it is responsible for handling the sprites that will be displayed on the screen (cubes, score, background). The methods that both classes have allow:

- Load images
- Clear the screen
- Update the screen
- Initialize SDL and its components
- Free textures
- Draw textures at a position
- Texture width and height variables, pixel positions where it will be rendered

Another class will be named GAME and will have all the data from the board, tetromino, and rect, and they will be related in it.

This class will have:

- PosX and posY of WHERE the Tetromino falls on the board
- A function that checks at the beginning if the piece can fit on the board, to trigger GameOver
- Variables like the height of a cube in pixels, upcoming Tetromino positions, next Tetromino (and its rotation)
- It has a board object and pointers to the Tetrominos
- A function that starts the game by getting two pieces and setting the level and wait time.
- A function that will be responsible for drawing the points, cubes, and the board.
- A RAND function to generate a random piece
- Another method that erases the current tetromino and points to the next piece
- The drawing function takes the textures and reads the board and the pieces to render them.
- A method that converts matrix coordinates to pixel coordinates on the board.
- A level counter and a lines cleared counter. The score is equal to 100 points per level and 10 points per line cleared.
- A method that handles events, so a switch (with cases for the pressed keys) should do the relevant actions, speeding up the piece, moving it, and rotating it.

Our main initializes textures, screen data, music, board and game variables, and takes the time (SDL_GetTicks()). It has a main loop that decides when the game should save the piece on the board and when it should move the piece down by one block.

SDL allows us to capture the window and keys, so with a WHILE loop, we can say, "as long as the window is not closed, the game continues."
