# 3D Engine Project

## Project Description

This project is a custom 3D engine developed as part of the fourth-year curriculum at ESIEE Engineering School. It utilizes SFML solely for writing pixels to the window from a custom image buffer. Every aspect of the image generation process is 100% custom-made, including a bespoke Color class, which features a `.toSFML()` method for compatibility with SFML. The engine is crafted to be lightweight and educational, aiming to showcase the principles of 3D graphics programming in detail.

## Quick Start

Clone the repository, install dependencies, compile the project, and run a basic demo using the following commands:

```bash
git clone git@github.com:GMoxFr/3d-engine.git
cd 3d-engine
./install_dependencies.sh
make
./3d-engine -C assets/confs/sample_config.json
```

## Installation

### Linux

#### Dependencies

Install the required dependencies:
```bash
apt-get install build-essential libsfml-dev make nlohmann-json3-dev
```
Alternatively, run the provided script: 
```bash
./install_dependencies.sh
```

#### Compilation and Execution

Follow the standard make commands to compile and execute the project as detailed in the original guide.

### macOS

Installation steps for macOS are similar to Linux, using Homebrew for package management.

#### Dependencies

Install the required dependencies:
```bash
brew install sfml openal-soft make nlohmann-json
```
Alternatively, run the provided script: 
```bash
./install_dependencies.sh
```

#### Compilation and Execution

Follow the standard make commands to compile and execute the project as detailed in the original guide.

## Development

The project's architecture is clearly structured with source files, headers, and error logs each in their respective directories. A detailed layout is provided in the original guide.

### Configuration and Assets

- Demo configuration files are located in assets/confs/*.json.
- Textures should be placed in assets/textures/* with .png or .jpg formats.

### Possible Improvements and Roadmap

- [x] Implementation of a more efficient raytracing algorithm (that avoid checking every object in the scene for a single ray but rather only the closest object that that ray intersects).
- [ ] Add examples and screenshots to the README.
- [x] Improved shadow computation for more realistic rendering.
- [ ] Implementation of PointLight to complement the existing Directional and Ambient Light.
- [ ] Documentation and API reference.

### How to do Profiling

To profile the project, we're using `gprof`. To do so, compile the project using `make profiling` and run the executable. Then, execute the following command:

```bash
gprof 3d-engine gmon.out > analysis.txt
```

## Examples and Screenshots

TODO