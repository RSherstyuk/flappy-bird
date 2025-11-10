# Flappy Bird Clone (Qt/C++)

This is a simple clone of the classic Flappy Bird game, implemented using C++ and the Qt framework.

## Project Structure

*   `main.cpp`: Entry point of the application, initializes the Qt application and the main window.
*   `src/Core/MainWindow.h`/`MainWindow.cpp`: Defines the main application window which hosts the game widget.
*   `src/Game/GameWidget.h`/`GameWidget.cpp`: Implements the core game logic, including bird movement, pipe generation, collision detection, and rendering.
*   `src/Game/Constants.h`: Contains various constants used in the game (e.g., window size, bird properties, pipe properties).

## Building the Project

This project uses CMake. To build it, follow these steps:

1.  **Install Qt 6:** Ensure you have Qt 6 installed on your system. You can download it from the [official Qt website](https://www.qt.io/download).
2.  **Install CMake:** Make sure CMake is installed.
3.  **Navigate to the project root:** Open your terminal and change directory to the root of this repository.
4.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```
5.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```
6.  **Build the project:**
    ```bash
    cmake --build .
    ```

## Running the Game

After successfully building the project, you can run the executable from the `build` directory:

```bash
./FlappyBirdQt
```

## How to Play

*   **Spacebar:** Press the spacebar to make the bird flap and move upwards.
*   **Objective:** Navigate the bird through the gaps in the pipes without hitting them or the ground/ceiling.

## Controls

*   **Spacebar:** Flap / Start Game
