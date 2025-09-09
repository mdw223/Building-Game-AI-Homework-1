# Boid Simulation

A simple 2D boid simulation built with C++ and SFML (Simple and Fast Multimedia Library). This program features two modes: starting with a simple single boid demonstration, then transitioning to a complex multi-boid simulation with animated sprites that follow a rectangular path around the screen, spawning sequentially in a chain-like pattern.

## Overview

The simulation begins in **Simple Mode** with a single boid moving horizontally across the screen. Users can click the "Click for more boids" button to activate **Complex Mode**, which features boids (bird-like objects) that move in a clockwise rectangular pattern around the screen. When a boid reaches the downward portion of its path, it triggers the spawning of the next boid in the sequence. Once all boids have completed their cycle and the last one reaches the top, the simulation resets after a 2-second pause.

### Simple Mode (Initial State, PART 2 OF PROJECT)
- Single boid moves horizontally from left to right
- Automatically resets to the left edge when reaching the screen boundary
- Interactive button displayed at the bottom: "Click for more boids"

### Complex Mode (After Button Click, PART 3 OF PROJECT)
- Multiple boids follow rectangular movement patterns
- Sequential spawning system
- Automatic simulation reset after completion

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

### Movement Patterns

#### Simple Mode Movement
- **Horizontal**: Moves from left to right at constant speed
- **Reset**: Returns to left edge upon reaching right boundary

#### Complex Mode Movement
1. **RIGHT**: Moves horizontally until reaching the right edge
2. **DOWN**: Moves vertically downward (triggers next boid spawn)
3. **LEFT**: Moves horizontally until reaching the left edge  
4. **UP**: Moves vertically upward until reaching the top

## User Interaction

### Controls
- **Simple Mode**: Click the blue "Click for more boids" button to transition to complex mode
- **Complex Mode**: Automatic operation, no user input required
- **Window**: Close using standard window controls

## Configuration

### Default Settings
- **Window Size**: 640x480 pixels
- **Number of Boids (Complex Mode)**: 4
- **Horizontal Speed (Complex Mode)**: 8.0 pixels per update
- **Vertical Speed (Complex Mode)**: 6.0 pixels per update
- **Simple Mode Speed**: 10.0 pixels every 100 frames
- **Update Frequency**: Every 100 frames
- **Reset Delay**: 2 seconds

### Customization
You can modify these parameters in the code:

```cpp
// in Boid class, keep ratio of 3 : 4 for speeds
Boid(const sf::Texture& texture, float speedH = 6.0f, float speedW = 8

// In main()
BoidManager boidManager(texture, 4, width, height); // numBoids, width, height

// In BoidManager constructor
boids.emplace_back(texture, 6.0f, 8.0f, winWidth, winHeight); // speedH, speedW

// Simple mode movement speed
sprite.move(10.0f, 0.0f); // Horizontal movement in simple mode
```

## File Structure
```
project/
├── main.cpp          # Source code
├── Makefile          # Build configuration
├── boid-sm.png       # Sprite image (required)
├── arial.ttf         # Font file (optional, for button text)
└── README.md         # This file
```

## Development Notes

This project was developed as a homework assignment for a Building Game AI course. Portions of the code (threading, timing, constructor implementations, and user interface button) were generated with assistance from ChatGPT, as noted in the source code comments.

The dual-mode design demonstrates progression from basic sprite movement to complex multi-agent behavior simulation.

## License

This is an educational project. Please respect any academic integrity policies if using this code for coursework.