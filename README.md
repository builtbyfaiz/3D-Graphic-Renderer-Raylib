# Ludo-Cpp-Raylib

A work-in-progress 3D renderer
Built with C++ and Raylib 5.5
## Status
In development, not feature complete.

## Controls
| Input | Action |
|-------|--------|
| WASD  | Move around |
| OP    | Change Modes of movement (Shapes/Camera) |

## Building

### Prerequisites
- MinGW-W64 or Visual Studio 2022
- Git

### Windows (MinGW)
```
build-MinGW-W64.bat
make
```

### Windows (Visual Studio)
```
build-VisualStudio2022.bat
```
Then open the generated `.sln` file.

### Linux
```
cd build
./premake5 gmake
cd ..
make
```

### MacOS
```
cd build
./premake5.osx gmake
cd ..
make
```

## Output
Built binary will be in `bin/debug`.