# Keybinds
## Movement
Q - Zoom in
E - Zoom out

W - Move camara UP
A - Move camara LEFT
S - Move camara DOWN
D - Move camara RIGHT

## File Save
CTRL+S - Open Save Menu
CTRL+o - Open Load Menu

## Menu
ESC - Return to Menu

## Editor Mode
SPACE - Editor Mode

# Tools

Eraser          - Erase Entities
Barrier         - Build unpassable Walls
Empty Creature  - Place an Empty Creature with Empty Neural Network
Food            - Place single Food cell
Food Spawner    - Place Food spawner
Inspector       - Allows selection of a Creature to inspect its values
Medusa          - Turns any Entity to Stone (Barrier)

# Building

Libraries used: 

## External
> imgui
> sfml
> xoshiro

## Self-made
> nanocomp
> stdxx

All libraries are in the libs folder, so it should build right away without having to install anything.
If pulling from github you will have to also specifiy --recursive to pull in the self-made libraries.

```
git clone git@github.com:JeneLitsch/creature-simulator.git --recursive
```

## Linux
Running `build.sh` or `make build` builds the project and puts the binary in `./build/bin/app`
Running `run.sh` just executes the binary
