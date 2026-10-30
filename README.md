# cub3D — Overdose Simulator

`cub3D` is a 42 project inspired by *Wolfenstein 3D*. It renders a first-person
maze from a `.cub` description using raycasting and MiniLibX. This version has
a Backrooms-inspired setting, mouse look, jumping, animated movement, floor and
ceiling rendering, and collectible pills.

## Features

- DDA-style raycasting with textured north, south, east, and west walls.
- Floor rendering with a configurable RGB color.
- A solid-color or XPM-textured ceiling.
- Collision-aware movement and smooth keyboard input.
- Mouse look and left/right rotation.
- Jumping and walking-height animation.
- A minimap and 20 randomly placed pill sprites.
- A simple game loop: collect pills, reach level 10, and win by overdosing.

## Requirements

The project targets Linux and uses the X11 version of
[MiniLibX](https://github.com/42Paris/minilibx-linux). Install the usual X11
development packages before compiling:

```sh
sudo apt-get install build-essential libxext-dev libx11-dev
```

## Build and run

From the repository root:

```sh
make
./cub3d maps/backroom.cub
```

Other sample maps are available in [`maps/`](maps/). To remove build files:

```sh
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # rebuild from scratch
```

## Controls

| Key | Action |
| --- | --- |
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| Left / Right arrows | Rotate |
| Mouse | Look around |
| `Shift` | Move faster while held |
| `Space` | Jump |
| `L` | Take a drug |
| `Ctrl` | Lock or unlock the mouse |
| `Esc` | Quit |

Pills are collected by walking close to them. The game ends when the player
reaches level 10, or when the overdose timer expires.

## Map format

The executable accepts one argument, and its filename must end in `.cub`.
The descriptor contains texture and color directives followed by the map:

```text
NO textures/textwall_v2.xpm
SO textures/textwall_v2.xpm
WE textures/textwall_v2.xpm
EA textures/textwall_v2.xpm
F 40,10,10
C textures/ceiling.xpm

111111
100001
10E001
100001
111111
```

### Directives

- `NO`, `SO`, `WE`, `EA`: XPM paths for the four wall directions.
- `F R,G,B`: floor color, with each component in the range `0–255`.
- `C R,G,B` or `C <path>`: ceiling color or XPM texture. This directive is
  required by the current loader.

### Map characters

- `1`: wall.
- `0`: walkable space.
- `N`, `S`, `E`, `W`: the single player spawn position and initial direction.
- Spaces may be used for map padding, but every walkable cell must be enclosed
  by valid map content. Maps with invalid characters, open boundaries, or no
  valid player position are rejected.

The repository includes example maps such as
[`maps/backroom.cub`](maps/backroom.cub) and
[`maps/lab.cub`](maps/lab.cub).

## Project structure

```text
includes/                 Shared headers and data structures
maps/                     Example .cub maps
textures/                 XPM wall, ceiling, and pill textures
srcs/main/                Startup, initialization, and error handling
srcs/map/                 Map extraction and validation
srcs/raycasting/          Raycasting, textures, sprites, and floor rendering
srcs/game_management/     Input, movement, game loop, minimap, and items
srcs/get_next_line/       Line-by-line file reading
srcs/utils/               String, color, image, and cleanup helpers
minilibx/                 Bundled MiniLibX source
```

The main rendering path casts one ray per screen column, determines the first
wall hit, samples the corresponding wall texture, and then draws sprites using
the ray depth buffer. Map validation happens before the graphical window is
created, so malformed `.cub` files fail early.

## 42 subject

This project implements the core `cub3D` requirements: parsing a map file,
validating a closed map, placing the player, displaying a first-person
raycasted view, loading XPM textures, handling movement and rotation, and
closing cleanly through MiniLibX events. The additional gameplay systems are
part of this project's Backrooms/Overdose Simulator extension.
