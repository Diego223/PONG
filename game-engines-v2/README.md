## Pong

In this exercise, you will create a simple Pong game by modifying the given Game class. You will need to update the initialization, setup, event handling, game state update, rendering, and cleanup methods to support the Pong game mechanics. The game should consist of two paddles and a ball that bounces between them. When a player scores a point by getting the ball past their opponent's paddle, the game should print the name of the player who scored and exit the game. This exercise will help you understand the different stages of the game loop and how they work together to create a functional game. Remember to focus on the core mechanics and not to worry about implementing a scoring system or other advanced features at this point, as this is just an introductory exercise.

1. Your task is to modify the Game class to create a Pong game.

2. Initialize the game window:
   - Update the 'init' method in the Game class.
   - Set up the game window with a title, width, and height.

3. Set up game objects and variables:
   - Update the 'setup' method in the Game class.
   - Create and initialize two paddle objects for the players.
   - Create and initialize a ball object.
   - Define variables for player names, ball speed, and paddle speed.

4. Handle user input and events:
   - Update the 'handleEvents' method in the Game class.
   - Process keyboard input for moving the paddles up and down.
   - Ensure that the paddles do not move outside the game window.

5. Update the game state:
   - Update the 'update' method in the Game class.
   - Update the position of the ball according to its speed and direction.
   - Check for collisions between the ball and the paddles.
   - Check for collisions between the ball and the top and bottom edges of the game window.
   - Check if the ball goes past a paddle, indicating a point has been scored. If so, print the name of the player who scored and exit the game.

6. Render the game objects:
   - Update the 'render' method in the Game class.
   - Clear the screen.
   - Draw the paddles and ball on the screen.

7. Cleanup:
   - Update the 'clean' method in the Game class.
   - Release any resources used by the game, such as textures.