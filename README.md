# Boid Simulation

A simple 2D boid simulation built with C++ and SFML (Simple and Fast Multimedia Library). This program creates animated sprites that follow a rectangular path around the screen, spawning sequentially in a chain-like pattern.

## Overview

The simulation features boids (bird-like objects) that move in a clockwise rectangular pattern around the screen. When a boid reaches the downward portion of its path, it triggers the spawning of the next boid in the sequence. Once all boids have completed their cycle and the last one reaches the top, the simulation resets after a 2-second pause.

## Features

- **Sequential Spawning**: Boids appear one after another as the previous boid reaches a specific point
- **Rectangular Movement Pattern**: Each boid follows a clockwise rectangular path (right → down → left → up)
- **Automatic Reset**: The simulation restarts when all boids complete their cycle
- **Cross-Platform**: Supports both macOS and Linux systems
- **Configurable**: Easy to modify number of boids, speeds, and window dimensions

## Prerequisites

### SFML Installation

#### macOS
```bash
# Using Homebrew
brew install sfml

# Using MacPorts
sudo port install sfml
```

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

#### Arch Linux
```bash
sudo pacman -S sfml
```

### Required Asset
The program requires a sprite image file named `boid-sm.png` in the same directory as the executable. This file should contain the visual representation of your boid.

## Building and Running

### Quick Start
```bash
# Build the program
make

# Run the simulation
./main

# Clean build files (optional)
make clean
```

### Build Requirements
- C++17 compatible compiler
- SFML graphics, window, and system libraries
- Make utility

### Supported Platforms
The Makefile automatically detects your platform and configures the appropriate compiler and library paths:

- **macOS**: Uses clang++ with Homebrew paths (Apple Silicon) or system paths (Intel)
- **Linux**: Uses g++ with standard system library paths

## Program Structure

### Classes

#### `Boid`
Represents a single animated sprite with the following features:
- Position and movement tracking
- Direction-based rotation (0°, 90°, 180°, 270°)
- Visibility control
- Boundary detection for path changes
- Configurable movement speeds

#### `BoidManager`
Manages multiple boids with:
- Automatic spawning logic
- Update frequency control (every 100 cycles)
- Reset functionality
- Batch rendering

### Movement Pattern
1. **RIGHT**: Moves horizontally until reaching the right edge
2. **DOWN**: Moves vertically downward (triggers next boid spawn)
3. **LEFT**: Moves horizontally until reaching the left edge  
4. **UP**: Moves vertically upward until reaching the top

## Configuration

### Default Settings
- **Window Size**: 640x480 pixels
- **Number of Boids**: 4
- **Horizontal Speed**: 8.0 pixels per update
- **Vertical Speed**: 6.0 pixels per update
- **Update Frequency**: Every 100 frames
- **Reset Delay**: 2 seconds

### Customization
You can modify these parameters in the code:

```cpp
// in Boid class, keep ratio of 3 : 4 for speeds
Boid(const sf::Texture& texture, float speedH = 36.0f, float speedW = 48
// In main()
BoidManager boidManager(texture, 4, width, height); // numBoids, width, height

// In BoidManager constructor
boids.emplace_back(texture, 6.0f, 8.0f, winWidth, winHeight); // speedH, speedW
```

## File Structure
```
project/
├── main.cpp          # Source code
├── Makefile          # Build configuration
├── boid-sm.png       # Sprite image (required)
└── README.md         # This file
```

## Controls
- **Close Window**: Click the X button or press Alt+F4 (platform dependent)
- **Automatic Operation**: The simulation runs continuously without user input

## Troubleshooting

### Common Issues

1. **"Error loading texture!"**
   - Ensure `boid-sm.png` exists in the same directory as the executable
   - Check that the image file is not corrupted

2. **Build failures**
   - Verify SFML is properly installed
   - Check that you have a C++17 compatible compiler
   - Make sure you're using the correct compiler for your platform

3. **Library linking errors**
   - Update the Makefile paths if SFML is installed in a non-standard location
   - Verify all SFML components (graphics, window, system) are installed

### Platform-Specific Notes

#### macOS
- The Makefile is configured for Apple Silicon Macs by default
- Intel Mac users may need to adjust the include/library paths
- Ensure Xcode Command Line Tools are installed

#### Linux (Grading Environment)
- Designed specifically for Ubuntu 20.04 Desktop
- Uses gcc compiler with standard system library paths
- Must work with only `build-essential` and `libsfml-dev` packages
- Test thoroughly in this environment before submission

## Development Notes

This project was developed as a homework assignment for a Building Game AI course. Portions of the code (threading, timing, and constructor implementations) were generated with assistance from ChatGPT, as noted in the source code comments.

## License

This is an educational project. Please respect any academic integrity policies if using this code for coursework.
