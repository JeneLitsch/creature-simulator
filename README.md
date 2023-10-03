# Keybinds
## Movement
Q - Zoom in
E - Zoom out

W - Move camara UP
A - Move camara LEFT
S - Move camara DOWN
D - Move camara RIGHT

## File Save
CTRL+S - Save Menu aufrufen
CTRL+o - Load Menu aufrufen

## Menu
ESC - Return to Menu

## Editor Modus
SPACE - Editor Modus

# Tools

Eraser          - Erase Entities
Barrier         - Build unpassable Walls
Empty Creature  - Place an Empty Creature with Empty Neural Netz
Food            - Place single Food cell
Food Spawner    - Place Food spawner
Inspector       - Allows selecting of Creature to Inspect its values
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

Running `build.sh` or `make build` builds the project and puts the binary in `./build/bin/app`
Running `run.sh` just executes the binary
