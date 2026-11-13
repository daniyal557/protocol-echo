# Protocol: Echo

A 2D grid-based mystery game written in C++ with a **raylib 5.5** graphical interface. Explore an abandoned village, collect objects, help a dog, solve a machine puzzle and confront a deceptive robot.

## Credits and history

An Object-Oriented Programming course project by **Abdullah Safeer** and **Daniyal Shafquat**, FAST-NUCES Karachi. Individual contributions have not been inferred from the proposal's numbered responsibility list.

This repository preserves the supplied game and artwork. Repository preparation in November 2026 added setup files and checks, normalized header/asset filename references, and added the explicit `<algorithm>` include needed by the renderer. The two supplied ZIP archives were byte-for-byte identical. Their originals remain unchanged.

## Start here

**`main.cpp` is the entry point.** It must be built together with all nine other root-level `.cpp` files. `display.cpp` implements the graphical interface. The implementation uses raylib, although the early proposal discussed SFML and console rendering.

### Code::Blocks on Windows

1. Install/configure a working MinGW GCC/G++ compiler in Code::Blocks.
2. Install raylib 5.5 built for the same compiler architecture and runtime. This computer already has its headers and libraries in `C:/raylib`.
3. Open **`ProtocolEcho.cbp`**. The project includes all game source files and links `raylib`, `opengl32`, `gdi32` and `winmm`.
4. If raylib is elsewhere, change the project Compiler search directory (`C:/raylib/include`) and Linker search directory (`C:/raylib/lib`).
5. Build and Run with the working directory set to the project root so `assets/` can be found. The supplied project sets this directory to `.`.

The game is not limited to Code::Blocks: any compatible C++17 build setup with raylib can compile it.

### Included build script

From PowerShell in this folder:

```powershell
.\build.ps1
.\build.ps1 -Compiler 'C:\path\to\g++.exe' -RaylibRoot 'C:\path\to\raylib'
```

The script prefers the working compiler found on this computer at `C:/mingw64ucrt/mingw64/bin/g++.exe`. The older installed Code::Blocks and Dev-C++ compiler executables failed to launch during preparation; in Code::Blocks, select a compiler profile using the working MinGW toolchain if needed.

The executable is `bin/ProtocolEcho.exe`. Double-click **`Run Game.cmd`** to launch with the correct working directory and local runtime search paths. If using a shared raylib library, its DLL must be discoverable at runtime; compiler runtime DLLs must also be available. Do not mix 32-bit and 64-bit libraries.

VS Code users can use the included build task; adjust the debugger/compiler path for another computer.

## Controls

| Key | Action |
| --- | --- |
| W / A / S / D | Move one tile; bump into characters to talk |
| Walk onto an object | Pick up or interact with it |
| E | Use the screw beside the hostile robot |
| 1 / 2 / 3 | Choose a machine puzzle action |
| Letters, Backspace, Enter | Enter and submit the final answer |
| Q | Quit during normal play |
| Escape | Close the game (see limitation below) |

## Code structure

- `entity.*`, `player.*`, `robot.*`, `dog.*`: entity hierarchy, player state and character interactions.
- `item.*`: collectible objects and the machine interaction.
- `map.*`, `tile.*`, `position.h`: 16 x 16 world, tile state and coordinate utilities.
- `puzzle.*`: machine sequence and final decoding logic.
- `display.*`: textures, camera, HUD, messages and puzzle screens.
- `gameLog.h`: session log output to `game_log.txt`.
- `assets/`: supplied PNG artwork.

## Validation and limitations

The complete game builds with GCC 13.1 and the installed raylib 5.5. Automated logic checks cover machine success/failure/reset, final answer handling, map unlocking and coordinate conversion. These checks do not replace a full interactive playthrough.

Existing gameplay limitations are preserved: no save/load, static NPCs, some long messages may overflow the panel, and session logging does not cover every ending branch. The machine screen says Escape steps back, but raylib's default Escape handling closes the window. Some supplied sprites have opaque backgrounds. Artwork provenance/licensing has not been established; no new reuse license is assigned to these assets.

Original reports containing student IDs are kept locally in `reference/`, excluded from Git. Generated binaries, editor state and session logs are also excluded.

## Run logic checks

From the root with a compatible `g++` on PATH:

```sh
g++ -std=c++17 -I. tests/logic_checks.cpp puzzle.cpp map.cpp tile.cpp entity.cpp -o bin/logic_checks
```

Run `bin/logic_checks.exe` on Windows or `bin/logic_checks` elsewhere.


A hidden-window graphics check also passed: the renderer initialized, loaded all 11 game textures, and rendered three frames without warnings. A full interactive playthrough remains unverified. Its source is in `tests/graphics_smoke.cpp`.
