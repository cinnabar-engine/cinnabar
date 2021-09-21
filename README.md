# Cinnabar Engine

[![Unit Testing](https://github.com/cinnabar-engine/cinnabar/actions/workflows/UnitTests.yml/badge.svg)](https://github.com/cinnabar-engine/cinnabar/actions/workflows/UnitTests.yml)
[![Code Quality](https://github.com/cinnabar-engine/cinnabar/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/cinnabar-engine/cinnabar/actions/workflows/codeql-analysis.yml)

## Prerequisites

Use the build tool [CMake](https://cmake.org/install/) to build cinnabar.

### Windows

Choose Compiler:

- [Visual Studio](https://visualstudio.microsoft.com/)/[MSBuild](https://aka.ms/buildtools) - _[setup](#visual-studio-installer)_
- [MinGW](http://mingw-w64.org/doku.php/download) - _[setup](#msysmingw)_

#### Visual Studio Installer

- Desktop development with C++ (C++ core desktop features)
- MSVC V142 - VS 2016 C++ x64/x86 build tools (Latest)
- Windows 10 SDK (10.0.19041.0)

Download and extract the [dependencies](#Dependencies) to a folder of your choosing,
set the environment variables of `GLM_ROOT_DIR` and `SDL2DIR`, add the bins of
pkg and glew to path, and put the .dll files in the res folder.

#### MinGW

```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S cmake mingw-w64-x86_64-glew mingw-w64-x86_64-glm mingw-w64-x86_64-SDL2
```

##### pkg-config

On the [gnome binaries website](https://download-fallback.gnome.org/binaries/),
navigate to win32 or win64 (for 32 or 64 bit), dependencies,
and download the latest non-dev versions of gettext-runtime and pkg-config.
Navigate back to the parent directory, glib, then download the latest non-dev version of glib.

### Debian

```bash
sudo apt install build-essential cmake libsdl2-dev libglew-dev libglm-dev libassimp-dev
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

Windows:

```
cd res
../build/run/cinnabar-engine.exe
```

Linux:

```
cd res
../build/run/cinnabar-engine
```

## Dependencies

- [CMake](https://cmake.org/)
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)
- [Simple Directmedia Layer](https://www.libsdl.org/)
- [GLEW](http://glew.sourceforge.net/)
- [OpenGL Mathematics](https://glm.g-truc.net/0.9.9/index.html)

## Libraries

- Build Pipeline: [CMake](https://cmake.org/)
- Library Helper: [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)
- Window: [Simple Directmedia Layer](https://www.libsdl.org/)
- Rendering: [OpenGL](https://www.opengl.org/)
- OpenGL Extention Loader: [GLEW](http://glew.sourceforge.net/)
- Maths: [OpenGL Mathematics](https://glm.g-truc.net/0.9.9/index.html)
- Image: [STB Image](https://github.com/nothings/stb/blob/master/stb_image.h)
- Text Files: [std:fstream](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/fstream.html)
- Logger: [Tumpnt Logger](https://github.com/Tumpnt/TumpntAudio/blob/master/src/core/tpnt_log.h)
- Time: [TumbleTime](https://github.com/tumble1999/tumble-time)

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Todo

Moved to: https://github.com/cinnabar-engine/cinnabar/projects/3

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
- [ ] Port to Windows
- [ ] Port to MacOS
- [ ] Port to Emscripten
- [ ] Port to Android
- [ ] Port to iOS

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
