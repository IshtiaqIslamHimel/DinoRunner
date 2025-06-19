# Dino Runner Console Game

A simple Chrome Dino-inspired game built using Raylib, featuring a scrolling background, player jumping mechanics, obstacles, scoring, and audio effects. This game includes a highest score tracker and credits the creator. Last updated: 02:51 AM +06, Friday, June 20, 2025.

## Table of Contents
- [Features](#features)
- [Controls](#controls)
- [Volume Control](#volume-control)
- [Installation](#installation)
- [How to Run](#how-to-run)
- [Gameplay](#gameplay)
- [Credits](#credits)
- [License](#license)
- [Contact](#contact)

## Features
- Scrolling cloud and background for a dynamic environment
- Player control with jumping mechanics using the spacebar
- Obstacles (cacti) that increase in speed every 10 passes
- Scoring system with a highest score record displayed in the top right
- Background music (BGM) and sound effects for jump and collision
- Volume control for audio adjustments
- Game over screen with restart option

## Controls
- **Spacebar**: Jump to avoid cacti
- **R**: Restart the game after a game over
- **Up Arrow**: Increase the volume of BGM and sound effects (up to 100%)
- **Down Arrow**: Decrease the volume of BGM and sound effects (down to 0%)

## Volume Control
The game allows real-time volume adjustment:
- Press the **Up Arrow** to increase the volume by 10% increments (max 100%)
- Press the **Down Arrow** to decrease the volume by 10% increments (min 0%)
- Initial volume is set to 50% for music and 70% for sound effects
- Volume changes apply to both background music and sound effects simultaneously

## Installation
### Prerequisites
- **Raylib**: Ensure Raylib is installed and configured. Download it from [raylib website](https://www.raylib.com/) or via a package manager
- **Compiler**: A C++ compiler (e.g., MSVC, GCC) with support for C++11 or later
- **Development Environment**: Visual Studio (recommended) or any IDE supporting C++ (e.g., Code::Blocks, VS Code)
- **Audio Files**: The game requires audio files in `.mp3` or `.wav` format

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/DinoRunnerConsole.git
   cd DinoRunnerConsole
   ```
2. Ensure the `raylib` library is included in the `raylib/` folder or linked via your build system
3. Copy all asset files (textures, audio, font) to the `resources/` folder:
   - `background.png` (1280x720)
   - `player.png` (205x203)
   - `cactus.png` (92x123)
   - `cloud.png` (1280x100)
   - `bgm.mp3` (background music)
   - `jump.wav` (jump sound effect)
   - `collision.mp3` (collision sound effect)
   - `Daydream.ttf` (custom font)
4. Open the project in your IDE (e.g., `DinoRunnerConsole.sln` for Visual Studio)

## How to Run
1. Build the project:
   - In Visual Studio, press `F7` to build
   - For other environments, compile with:
     ```bash
     g++ src/DinoRunnerConsole.cpp -o DinoRunnerConsole -lraylib -lopengl32 -lgdi32 -lwinmm
     ```
2. Run the executable:
   - In Visual Studio, press `F5` to run
   - Or execute the built file:
     ```bash
     ./DinoRunnerConsole
     ```
3. Ensure all resource files are in the correct directory relative to the executable

## Gameplay
- **Objective**: Jump over cacti to score points. The game ends if you collide with a cactus
- **Scoring**: Earn 10 points for each cactus passed. Speed increases by 5.0f every 10 cacti
- **Highest Score**: Displayed in the top right corner, updating with your best score
- **Game Over**: Occurs on collision; press 'R' to restart
- The current score is shown in the top left, and a creator credit appears at the bottom left

## Credits
- **Created by**: Ishtiaq Islam Himel
- **Game Engine**: Raylib (https://www.raylib.com/)



## Contact
- **Author**: Ishtiaq Islam Himel 
- **Email**: ishtiaqhimel11@gmail.com 
- **GitHub**: [IshTiaQ_](https://github.com/IshtiaqIslamHimel)
```

