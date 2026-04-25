# DVD Logo Screensaver

A customizable DVD bouncing logo screensaver with shader effects and sound.

## Features

- Bouncing DVD logo with collision sounds
- Rainbow color cycling effect
- Fullscreen and windowed modes
- Shader-based color effects

## Requirements

- [raylib](https://www.raylib.com/) (version 4.0 or newer)
- GCC or any C compiler

## Controls
- P - Pause/Rename
- UP/DOWN Volume control

## Flags

- -c  Borderless windowed mode
- -h  Hide cursor 

## Project Structure
    DVD-Screensaver/
    ├── src/
    │   ├── dvd_text.c          (text version)
    │   └── main.c              (texture + shader version)
    ├── res/
    │   ├── bop.mp3
    │   └── dvd.png
    ├── shaders/
    │   └── tint.fs
    └── README.md

## Notes
- Run the executable from the project root directory, it will search assets from there

- The texture version requires tint.fs in the shader file in addition to bop.mp3 and dvd_logo in the res folder

- Fullscreen mode is enabled by default (press ESC to exit)
