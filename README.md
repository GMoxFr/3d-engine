# 3d-engine

## Description

The goal of this project is to create a custom 3d engine, using SFML for the window.

## Installation

### Linux

#### Dependencies

- Build Essentials: `apt-get install build-essential`
- SFML: `apt-get install libsfml-dev`
- Make: `apt-get install make`

#### Compilation

Compile the project:
`make`

To recompile the project (this will clean and then compile again):
`make re`

To remove compiled object files:
`make clean`

To remove both compiled object files and the executable:
`make fclean`

#### Execution

Execute the project using
`./3d-engine`

### macOS

#### Dependencies

- Command Line Tools: `xcode-select --install`
- SFML: `brew install sfml`
- OpenAL: `brew install openal-soft`
- Make: `brew install make`

#### Compilation

Compile the project:
`make`

To recompile the project (this will clean and then compile again):
`make re`

To remove compiled object files:
`make clean`

To remove both compiled object files and the executable:
`make fclean`

#### Execution

Execute the project using
`./3d-engine`

## Development

### Architecture

The project is structured as follows:
 - The main function is in main/main.cpp
 - The source files are in src/*.cpp
 - The header files are in include/*.hpp
 - When compiling if errors are found they will be in errors/ directory