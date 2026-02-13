# Old Game Engine

## Overview

A custom game engine built from scratch in C++ as a learning project to understand the fundamentals of real-time graphics programming and game engine architecture. This engine demonstrates core rendering capabilities, resource management, and interactive 3D graphics using modern OpenGL.

## Key Features

- **Custom 3D Rendering Pipeline**: Built-in OpenGL-based rendering system for real-time 3D graphics
- **Shader System**: GLSL shader support for customizable rendering effects
- **Scene Management**: Hierarchical scene graph for organizing game objects
- **Resource Management**: Efficient loading and management of assets
- **Camera System**: Flexible camera controls for scene navigation
- **Input Handling**: Keyboard and mouse input system
- **Lighting**: Support for various lighting models and techniques

## Tech Stack

- **C++ (95.7%)**: Core engine architecture and systems
- **GLSL (3.4%)**: Custom shaders for rendering effects
- **C (0.9%)**: Low-level system interfaces
- **OpenGL**: Graphics API for rendering
- **Build System**: [CMake/Makefile/other - update as needed]

## How to Build

### Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- OpenGL 3.3 or higher
- CMake (if applicable)
- Graphics drivers supporting OpenGL

### Build Steps

```bash
# Clone the repository
git clone https://github.com/franfazzari/Old-Game-Engine.git
cd Old-Game-Engine
# make

```
## What I Learned
Through building this game engine from scratch, I gained hands-on experience with:

- **Graphics Programming**: Deep understanding of the OpenGL rendering pipeline, vertex/fragment shaders, and GPU programming
- **Engine Architecture**: Designing modular, maintainable systems for rendering, input, and resource management
- **3D Mathematics**: Implementing transformations, projections, and spatial calculations essential for 3D graphics
- **Memory Management**: Efficient resource handling and optimization techniques in C++
- **Real-Time Systems**: Managing frame timing, updates, and rendering loops for interactive applications
-** Shader Programming**: Writing GLSL shaders to achieve various visual effects
- **Software Design Patterns**: Applying patterns like Entity-Component-System, Object Pooling, and Observer patterns
-** Problem Solving**: Debugging complex rendering issues and performance bottlenecks
- This project served as a comprehensive exploration of game engine internals and low-level graphics programming, providing a strong foundation for future work in real-time rendering and interactive applications.
