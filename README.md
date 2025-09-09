# Boid Simulation

A simple 2D boid simulation built with C++ and SFML (Simple and Fast Multimedia Library). This program features two modes: a simple single boid demonstration and a complex multi-boid chain simulation that creates animated sprites following a rectangular path around the screen.

## Overview

The simulation starts in **Simple Mode** with a single boid moving horizontally across the screen in a basic loop. Users can click a button to transition to **Complex Mode**, which features multiple boids that move in a clockwise rectangular pattern around the screen, spawning sequentially in a chain-like pattern.

### Simple Mode
- Single boid moves horizontally from left to right
- Automatically resets to the left edge when reaching the right boundary
- Displays a "Click for more boids" button at the bottom of the screen

### Complex Mode
- Multiple boids follow a rectangular movement pattern
- Sequential spawning as each boid reaches the downward portion of its path
- Automatic reset when all boids complete their cycle after a 2-second pause

## Features

- **Dual Mode Operation**: Toggle between simple and complex boid behaviors
- **Interactive Button**: Click to transition from simple to complex mode
- **Sequential Spawning**: In complex mode, boids appear one after another as the previous boid reaches a specific point
- **Rectangular Movement Pattern**: Each boid follows a clockwise rectangular path (right → down → left → up)
- **Automatic Reset**: The complex simulation restarts when all boids complete their cycle
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

### Required Assets
- **Sprite Image**: `boid-sm.png` - The visual representation of your boid
- **Font File**: `arial.ttf` or another TrueType font for button text (optional - program will show warning if not found but still function)

Both files should be placed in the same directory as the executable.

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

### Movement Patterns

#### Simple Mode
- **Horizontal Movement**: Boid moves from left to right at a constant speed
- **Boundary Reset**: Returns to left edge when reaching the right boundary

#### Complex Mode
1. **RIGHT**: Moves horizontally until reaching the right edge
2. **DOWN**: Moves vertically downward (triggers next boid spawn)
3. **LEFT**: Moves horizontally until reaching the left edge  
4. **UP**: Moves vertically upward until reaching the top

## Configuration

### Default Settings
- **Window Size**: 640x480 pixels
- **Number of Boids (Complex Mode)**: 4
- **Horizontal Speed (Complex)**: 8.0 pixels per update
- **Vertical Speed (Complex)**: 6.0 pixels per update
- **Simple Mode Speed**: 10.0 pixels every 100 frames
- **Update Frequency**: Every 100 frames
- **Reset Delay**: 2 seconds

### Customization
You can modify these parameters in the code:

```cpp
// In Boid constructor, keep ratio of 3:4 for speeds
Boid(const sf::Texture& texture, float speedH = 6.0f, float speedW = 8.0f, ...)

// In main()
BoidManager* boidManager = new BoidManager(texture, 4, width, height); // numBoids, width, height

// In BoidManager constructor
boids.emplace_back(texture, 6.0f, 8.0f, winWidth, winHeight); // speedH, speedW

// Simple mode movement speed
sprite.move(10.0f, 0.0f); // Adjust horizontal movement speed
```

## File Structure
```
project/
├── main.cpp          # Source code
├── Makefile          # Build configuration
├── boid-sm.png       # Sprite image (required)
├── arial.ttf         # Font file (optional)
└── README.md         # This file
```

## Controls

### Simple Mode
- **Button Click**: Click the blue "Click for more boids" button to transition to complex mode
- **Window Controls**: Close window using the X button or platform-specific shortcuts

### Complex Mode
- **Automatic Operation**: The simulation runs continuously without user input
- **Window Controls**: Close window using the X button or platform-specific shortcuts

## Troubleshooting

### Common Issues

1. **"Error loading texture!"**
   - Ensure `boid-sm.png` exists in the same directory as the executable
   - Check that the image file is not corrupted

2. **"Warning: Could not load font. Button text may not display properly."**
   - Add `arial.ttf` to your project directory, or
   - Modify the font path in the code to point to an available system font
   - The program will still function without the font

3. **Build failures**
   - Verify SFML is properly installed
   - Check that you have a C++17 compatible compiler
   - Make sure you're using the correct compiler for your platform

4. **Library linking errors**
   - Update the Makefile paths if SFML is installed in a non-standard location
   - Verify all SFML components (graphics, window, system) are installed

5. **Button not responding**
   - Ensure you're clicking within the blue button area at the bottom of the screen
   - Check that mouse events are being processed correctly

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

This project was developed as a homework assignment for a Building Game AI course. Portions of the code (threading, timing, constructor implementations, and user interface button) were generated with assistance from ChatGPT, as noted in the source code comments.

The dual-mode design allows for easy demonstration of both basic sprite movement and more complex multi-agent behaviors.

## License

This is an educational project. Please respect any academic integrity policies if using this code for coursework.