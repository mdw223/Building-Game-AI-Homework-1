# Boid Simulation

A simple 2D boid simulation built with C++ and SFML (Simple and Fast Multimedia Library). This program creates animated sprites that follow a rectangular path around the screen, spawning sequentially in a chain-like pattern.

## Overview

The simulation features boids (bird-like objects) that move in a clockwise rectangular pattern around the screen. When a boid reaches the downward portion of its path, it triggers the spawning of the next boid in the sequence. Once all boids have completed their cycle and the last one reaches the top, the simulation resets after a 2-second pause.

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

## Development Notes

This project was developed as a homework assignment for a Building Game AI course. Portions of the code (threading, timing, and constructor implementations) were generated with assistance from ChatGPT, as noted in the source code comments.

## License

This is an educational project. Please respect any academic integrity policies if using this code for coursework.
