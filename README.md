# Cinnabar Engine

## Todo
* Risize context on window resize
* Time Class
* Camera Class
* Input System
* Render System
* Materials
* Mesh Importing
* Lights
* Collision
* Gravity
* Text
* Layers
* GUI
* States
* Map management
* Make an Actual Game
* Networking

* Scene Graph

* XML based scene graph import
* Test ON Windows
* Port to Emscrpten

## Prerequisites

Use the build tool [CMake](https://cmake.org/install/) to build cinnabar.

### Windows
[Visual Studio](https://visualstudio.microsoft.com/)

[VSCode](https://code.visualstudio.com/docs/cpp/config-msvc)
### Debian
```bash
sudo apt-get install build-essential cmake libsdl2-dev libglew-dev libglm-dev
```
### Arch
```bash
sudo pacman -S base-devel cmake make gcc ninja sdl
```
### Redhat/Fedora
```bash
sudo dnf install kernel-devel make automake gcc gcc-g++ ninja-build make
```
## building instrictions
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running
Windows: /build/run/(Debug/Release)/engine.exe
Linux: /build/run/engine

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
