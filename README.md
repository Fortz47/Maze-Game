# Maze Game with SDL2 and Raycasting

## Overview
This is a maze game implemented in C using the SDL2 library with raycasting techniques for rendering. The game features a maze environment where players navigate through corridors, avoiding collisions with walls. The game utilizes raycasting to simulate a 3D perspective, projecting walls, ceilings, and floors onto a 2D screen.

## Features
- **Maze navigation:** Players can move through the maze using keyboard controls.
- **Raycasting rendering:** Walls, ceilings, and floors are rendered using raycasting techniques to create a pseudo-3D effect.
- **Collision detection:** Players cannot move through walls; collision detection prevents them from passing through obstacles.
- **Map generation:** The game includes a map generation feature to create random maze layouts for dynamic gameplay.

## Installation
1. Clone the repository to your local machine:
    ```
    git clone https://github.com/your-username/maze-game.git](https://github.com/Fortz47/Maze-Game/
    ```
2. Navigate to the project directory:
    ```
    cd Maze-Game
    ```
3. Compile the game using a C compiler such as GCC:
    ```
    gcc .\src\*.c .\headers\maze.h -o app -I./SDL2/include/SDL2 -L./SDL2/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    ```
    Note that this is the compilation flags for MinGW on windows

5. Run the compiled executable:
    ```
    .\app.exe
    ```

## Controls
- Use the arrow keys or WASD keys to move the player character.
- Use the Left and right direction keys to control the camera.
- Press the ESC key to exit the game.

## Gameplay
- The objective of the game is to navigate through the maze and reach the exit.
- Players must avoid colliding with walls, as this will reset their position to the starting point.
- Navigate carefully through the maze to find the exit as quickly as possible.

## Authors
Atuokwu A. Fortune [Email](atuokwu.fortune@gmail.com) - [Github](https://github.com/Fortz47) - [Linkden](https://www.linkedin.com/in/fortune-atuokwu-427213186/)

## Contributions
Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.
It is still much a work in progress, more features will be added.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements
- Special thanks to the authors of the [SDL2 library](https://www.libsdl.org/) for providing the tools necessary to create this game.
- This project is one of the requirements for the completion my ALX software engineering program.
