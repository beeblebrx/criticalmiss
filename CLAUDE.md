# CLAUDE.md

This is a role playing game where the player controls a party of up to 4 characters.
The party moves as one in a dungeon drawn on a 2D grid of rooms and tunnels, fighting enemies and solving puzzles.

## Architecture

This game uses SFML 3 for window management, 2D graphics, keyboard events and sounds.

This project utilizes object oriented programming. Encapsulate everything in classes, main.cpp being the only exception.

Follow the Clean Architecture principles: create software that is flexible, maintainable, and testable by separating concerns into distinct layers. Two layers: inner and outer.

**`game/`** — the core, inner layer. Must remain dependency-free: no includes from other directories, or any external library (including SFML).

**`main.cpp`** — wires everything together. Keep it as short as possible; any non-trivial logic belongs in a namespaced module.

Renderer, event handler and future sound player and game save/load handling are in the outer layer.

## Tests

Utilize Google Test for testing. Tests are in **`tests/`**. After implementing a change update test cases that test the changed class or create new test suites for new classes. Then run tests.

If a test fails stop and tell how you plan to fix it and ask if you can continue.