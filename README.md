# -Chess-
Chess developed in C++ using features of OOP, and SFML for graphics.

# Overview
 - This project is a fully functional chess game developed in C++ using the Simple and Fast Multimedia Library (SFML) for graphics. The game is designed with Object-Oriented Programming (OOP) principles, ensuring a modular and maintainable codebase.

# Features
- Graphical Interface: The game features a user-friendly graphical interface powered by SFML.
- Full Chess Mechanics: Implements all standard chess rules, including piece movements, captures, check, checkmate, and stalemate.
- Two-Player Mode: Allows two players to play against each other on the same machine.
- Move Validation: Ensures all moves are valid according to chess rules.
- Highlighting: Highlights valid moves for the selected piece.
- Player Selection Logic: Manages turns and player interactions.
- Customizable Board: The board and pieces can be customized with different textures.

# Installation
- Prerequisites
- C++ Compiler: Ensure you have a C++ compiler installed (e.g., g++, clang++).
- SFML Library: Download and install SFML from SFML's official website

# Setting Up SFML for Your Project
- Prerequisites
- C++ Compiler: Make sure you have a C++ compiler installed (e.g., GCC for Linux, MinGW for Windows, or Xcode for macOS).
- SFML Library: Download and install the SFML library from the official SFML website.
- Windows
 - Download SFML: Go to the SFML download page and download the version compatible with your compiler (e.g., GCC MinGW).
- Extract SFML: Extract the downloaded SFML files to a directory of your choice (e.g., C:\SFML).
- Configure Your Project:
- In your project settings, add the path to the SFML headers (e.g., C:\SFML\include) to the include directories.
- Add the path to the SFML libraries (e.g., C:\SFML\lib) to the library directories.
- Link against the SFML libraries (e.g., sfml-graphics.lib, sfml-window.lib, sfml-system.lib). If you're using dynamic linking, also link against the corresponding -d versions for the debug configuration (e.g., sfml-graphics-d.lib).

# Usage
- Start Game: Run the executable to start the game.
- Control Pieces: Use the keyboard arrow keys and enter button to select and move pieces.
- Quit Game: Close the window or use an exit option provided in the main menu.

# Acknowledgements
- SFML: The graphics library used for rendering the game.
- Open Source Community: For various tutorials and resources that helped shape this project.
