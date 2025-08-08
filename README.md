# Isometric

A simple C-based isometric map renderer and editor, built using SDL.

## Features
- Layered isometric map rendering with SDL (C)
- Load and display tile maps from text files (e.g., `resources/map.txt`)
- Interactive **MapMaker** tool:
  - Choose tiles by clicking (keyboard or mouse)
  - Navigate layers, pan and zoom the viewport
  - Save custom map edits back to a file
- Core components include:
  - Isometric map loading & rendering (`mapISO.*`)
  - Utility functions for input, collision detection, text rendering (`toolSDL.*`)
  - MapMaker UI logic for editing and saving (`map_maker.*`)
  - Game loop handling input and rendering (`game.*`)
  - SDL initialization and teardown (`initSDL.*`)

## Getting Started

### Prerequisites
- C compiler (e.g., gcc)
- SDL2, SDL_image, SDL_ttf, SDL_mixer libraries installed

### Build
```bash
make && make run
`````
## Usage

- **F key**: `F` – Enter map-making mode  
- **Mouse-click**: Paint the selected tile on the map  
- **N key**: `N` – Cycle through tiles  
- **P / M keys**: `P` / `M` – Zoom in / out  
- **L key**: `L` – Change layer  
- **Esc key**: `Esc` – Exit editor or program  
- **In editor mode**: Edited maps are saved back to `resources/map.txt`
