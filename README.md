**Chess Game Simulator in C++**

**Project Overview**
This project is a C++ implementation of a chess game simulator. It accurately simulates and manages chess games by loading game states from Forsyth–Edwards Notation (FEN) strings and processes moves inputted by users. The primary focus of this project is to demonstrate advanced C++ programming skills and object-oriented design principles.

**Features**
- FEN String Parsing: Loads and interprets chess game states from Forsyth–Edwards Notation, providing a versatile starting point for game simulations.
- Chess Piece Movement Validation: Each chess piece is represented by a specific class, with its own logic to validate legal moves according to standard chess rules.
- Game State Management: Tracks the ongoing state of the chess game, including turn management, piece positions, and game status (e.g., check, checkmate, stalemate).
- User Interaction: Accepts user input for moves in a standard chess format (source square to destination square) and provides feedback on move legality and game progression.

Technical Implementation
- Object-Oriented Design: Utilizes classes and inheritance to represent different chess pieces, encapsulating their specific movement behaviors and interactions.
- C++ Standard Template Library (STL): Makes effective use of the STL for efficient data handling and manipulation.
- Error Handling: Implements robust error checking to handle invalid inputs and game state anomalies.
