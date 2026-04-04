# CLAUDE.md

This is a role playing game where the player controls a party of up to 4 characters.
The party moves as one in a dungeon drawn on a 2D grid, fighting enemies and solving puzzles.

## Architecture

This game uses SFML 3 for window management, 2D graphics, keyboard events and sounds.

This project utilizes object oriented programming. All code in the project must be encapsulated in classes, main.cpp being the only exception.

Follow the Clean Architecture principles: focus on creating software that is flexible, maintainable, and testable by separating concerns into distinct layers. 

**`game/`** — the core domain layer. Must remain dependency-free: no includes from other directories, or any external library (including SFML). All other layers may depend on `game/`, never the reverse.

**`main.cpp`** — wires everything together. Keep it as short as possible; any non-trivial logic belongs in a namespaced module.
