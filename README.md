# Cardboard

Cardboard is my first ever game engine, it is not really intended to be used.

Libraries used:
- GLFW
- Spdlog

## Using the engine

Currently the engine is kind of hard to use, but the easiest would be to clone this project and clean out the `Game` project and you will have a clean slate for your game.

## Contributing

Clone the project
```sh
git clone --recursive https://www.github.com/Sebastian2852/Cardboard.git
```

Then using [Premake](https://github.com/premake/premake-core/) you can create project files.
Here is an example for visual studio 2022 projects:
```sh
premake vs2022
```
To see more please see [here](https://premake.github.io/docs/Using-Premake).

---

## Todo
- [x] Layer system
- [x] Add GLAD
- [ ] Event system
- [x] Proper logging
    - [x] Logging should only be enabled in debug builds

---
