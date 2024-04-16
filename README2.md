# 3d-engine

## Description

The goal of this project is to create a custom 3d engine, using SFML for the window.

## Installation

### Linux

Here's what you need to do to work on this project on Linux.

#### Dependencies

- Build Essentials: `apt-get install build-essential`
- SFML: `apt-get install libsfml-dev`
- Make: `apt-get install make`
- JSON for Modern C++: `apt-get install nlohmann-json3-dev`

Or you can install all the dependencies using `apt-get install build-essential libsfml-dev make nlohmann-json3-dev` or execute the `install_dependencies.sh` script with `./install_dependencies.sh`.

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
`./3d-engine --help`

### macOS

Here's what you need to do to work on this project on macOS.

#### Dependencies

- Command Line Tools: `xcode-select --install`
- SFML: `brew install sfml`
- OpenAL: `brew install openal-soft`
- Make: `brew install make`
- JSON for Modern C++: `brew install nlohmann-json`

Or you can install all the dependencies using `brew install sfml openal-soft make nlohmann-json` or execute the `install_dependencies.sh` script with `./install_dependencies.sh`.

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
`./3d-engine --help`

## Development

### Architecture

The project is structured as follows:
 - The main function is in main/main.cpp
 - The source files are in src/\*\*/*.cpp
 - The header files are in include/\*\*/*.hpp
 - When compiling if errors are found they will be in errors/ directory

### Possible improvements

- [x] For the Ray-Tracing, only check the closest object for each ray.
- [ ] Upgrade shadows for the Ray-Tracing. Currently, the shadows are not very realistic as they're only compute if a shape is between the light and the object. It would be better to compute the shadows using the Ray-Tracing.

