This project is a fully playable Chess game written in C++ for CS246 Spring 2025.

It’s built using a Model-View-Controller (MVC) design with the Observer pattern, which keeps the board, displays, and game state in sync.

The game logic is handled by GameState and Board, which track turns, validate moves, and handle special rules like check, checkmate, stalemate, and en passant.

The user interface includes both a text-based display and a graphical X11 display, both of which update automatically when the board changes.

The computer player comes in three difficulty levels: from random legal moves (Level 1) to more strategic play that avoids captures and prioritizes checks (Level 3).

Other features include safe memory management, support for custom board setups, and a bonus mode with Unicode chess piece symbols in the terminal.
