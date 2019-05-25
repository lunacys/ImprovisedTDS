# ImprovisedTDS

A simple Top-Down Shooter game written in C++ using GLFW and OpenGL. As it mentioned in the repo's name, this game is totally improvised and does not have a plan on its development.

## TODO

- [x] Add existing sources
- [x] Make all libraries to be in the repo as submodules and change C++ directories path
  - [x] GLFW
  - [x] ~~zlib~~
  - [x] ~~lpng~~ use `stb_image` instead
  - [x] ~~glew~~ use `glad` instead
  - [x] glm
  - [x] stb_image
- [x] Reorder source files to be in `src` directory instead of directory with the VS project file, do the same with the headers
- [x] Convert Visual Studio project to CMake
- [x] Make the project to be working
- [x] Use stb_image library for reading and writing image assets instead of lpng
- [ ] Fix textures not being showing correctly

