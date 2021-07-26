# Cinnabar Engine

## Prerequisites

Use the build tool [CMake](https://cmake.org/install/) to build cinnabar.

### Windows
#### Manual
[Visual Studio](https://visualstudio.microsoft.com/)
[VSCode](https://code.visualstudio.com/docs/cpp/config-msvc)
#### winget
Install [winget](https://docs.microsoft.com/en-us/windows/package-manager/)
```powershell
winget install //TODO: look in https://github.com/microsoft/winget-pkgs
```
#### Chocolaty
Install [Chocolaty](https://chocolatey.org/install)
```powershell
choco install //TODO: look in https://community.chocolatey.org/packages
```
#### Scoop
install [scoop](https://scoop.sh/)
```powershell
scoop install //TODO: look in https://github.com/ScoopInstaller/Main
```
#### Windows Subsysytem for Linux
* [Debian/Ubuntu](#debian-ubunto)
* [Arch](#arch)
#### MinGW
Install [MSYS2](https://www.msys2.org/#installation)
```bash
pacman -S cmake //TODO: look in https://packages.msys2.org/queue
```
### Mac OS X
Install [Homebrew](https://brew.sh/)
```bash
brew install cmake //TODO: look in https://formulae.brew.sh/formula/
```

### Debian/Ubuntu
```bash
sudo apt install build-essential cmake libsdl2-dev libglew-dev libglm-dev libassimp-dev libfreetype-dev
```
### Arch
```bash
sudo pacman -S base-devel cmake sdl2 glew glm assimp
```
### Redhat/Fedora
```bash
sudo dnf install kernel-devel cmake sdl // TODO
```
## Build Instructions
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running
Windows: /build/run/(Debug/Release)/engine.exe
Linux: /build/run/engine

## Libraries
* Build Pipeline: [CMake](https://cmake.org/)
* Window: [Simple Directmedia Layer](https://www.libsdl.org/)
* Rendering: [OpenGL](https://www.opengl.org/)
* OpenGL Extention Loader: [GLEW](http://glew.sourceforge.net/)
* Maths: [OpenGL Mathematics](https://glm.g-truc.net/0.9.9/index.html)
* Image: [STB Image](https://github.com/nothings/stb/blob/master/stb_image.h)
* Text Files: [std:fstream](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/fstream.html)
* Font Renderer [FreeType](https://www.freetype.org/)
* Logger: [Tumpnt Logger](https://github.com/Tumpnt/TumpntAudio/blob/master/src/core/tpnt_log.h)
* Time: [TumbleTime](https://github.com/tumble1999/tumble-time)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Todo
 - [x] CMake
 - [x] Logger
 - [x] SDL2
 - [x] GLSL
 - [x] Triangle
 - [x] Vertex Colors
 - [x] Indices
 - [x] Shader Class
 - [x] Quad Rendering
 - [x] Texture Mapping
 - [x] Uniforms
 - [x] Mesh Class
 - [x] Texture Class
 - [x] Matricies
 - [x] Pespective Camera
 - [x] 3D Cube
 - [x] 3D Transforms
 - [x] WASD
 - [x] Basic input handling
 - [x] Mouse controlled camera
 - [x] Window Class
 - [x] Resize context on window resize
 - [x] Time Class
 - [x] Camera Class
 - [x] Smooth Input
 - [x] Materials
 - [x] Render System
 - [x] Multiple Objects rendering at the same time
 - [x] Mesh Importing
 - [x] Full UV mapping support
 - [x] Full vertex color support
 - [ ] Multi-texture materials
 - [x] Normals
 - [ ] Normal maps
 - [x] Matcaps (SArpnt will do this)
 - [ ] Simple object classes (combine assets and automatically manage render commands)
 - [ ] Depth manipulation
 - [ ] Skybox
 - [ ] GL lines
 - [ ] Sprites (i think you can do GL_POINTS and draw the images in a frag shader)
 - [ ] Supersampling and subsampling
 - [ ] Antialiasing
   - [ ] MSAA
   - [ ] FXAA
   - [ ] MSAA with FXAA
 - [ ] Mipmaps
 - [ ] Anisotropic filtering
  - [ ] Texture filtering
   - [ ] Nearest
   - [ ] Linear
   - [ ] Bilinear
   - [ ] Trilinear
  - [ ] Supersampling / subsampling interpolation
    - [ ] Nearest
    - [ ] Bilinear
    - [ ] Bicubic
    - [ ] Trilinear
    - [ ] Lanczos
 - [ ] Lights
 - [ ] Text
 - [ ] GUI
 - [ ] Portals
 - [ ] VR Support
 - [ ] Test on Windows
 - [ ] Port to Emscripten

### Physics engine (make a seperate project)

 - [ ] Shapes
   - [ ] Point
   - [ ] Line segment
   - [ ] Rectangular prism
   - [ ] Sphere
   - [ ] Cylinder
   - [ ] Capsule
   - [ ] Cone
   - [ ] Ngon prism
   - [ ] Elipsoid
   - [ ] Mesh
 - [ ] Shape collision
 - [ ] Shape advanced collision (Get information like position, speeds, collision normals, etc. so that physics can be done)
 - [ ] Physics
   - [ ] Air resistance
   - [ ] Friction
   - [ ] Bounciness
   - [ ] Buoyancy
   - [ ] Fake fluid (fluid in small comtainers like bottles, get water level)
   - [ ] Soft body
   - [ ] Fluid
 - [ ] Portals
 - [ ] Test on Windows
 - [ ] Port to Emscripten

### Networking (make a seperate project)

 - TODO: Make todo list

### SceneGraph (make a seperate project)

 - [ ] States
 - [ ] Scene Graph
 - [ ] Map management
 - [ ] XML based scene graph import

### Misc

 - [ ] Events System
 - [ ] Make an Actual Game
