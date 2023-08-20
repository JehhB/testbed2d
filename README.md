# Testbed2D

Testbed2D is a 2D graphical simulator for simulating/testing [PlatformIO](https://platformio.org/) projects.
It is created using [Box2D](https://box2d.org/) and [Dear ImGui](https://github.com/ocornut/imgui).

## Installation

Create an environment with Windows x86 platform then include Testbed2D as a dependency

```ini
[env:simulator]
platform = platformio/windows_x86@^1.2.0
lib_deps =
  https://github.com/JehhB/testbed2d.git
```