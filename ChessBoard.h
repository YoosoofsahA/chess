#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPieces.h"
#include <string>
#include <map>

// ChessBoard class declaration

class ChessBoard {

	public:

		/**
		 * Default ChessBoard class constructor that initiates the pieceMap
		 */
		ChessBoard();

		/** 
		 * ChessBoard destructor
		 */
		~ChessBoard();

		/**
		 * Loads a new chess board state from a FEN string representation.
		 * 
		 * @param boardState A null-terminated string representing the new board state.
		 * The format includes piece placement data and the active colour.
		 * Example: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq"
		 */
		void loadState(const char*);
		

		/**
		 * Submits a chess move from the source square to the destination square.
		 *
		 * @param sourceSquare A string representing the source square of the move (e.g., "A2").
		 * @param destSquare A string representing the destination square of the move (e.g., "A4").
		 * 
		 * The function validates the move, checks for legality, and updates the chess board accordingly.
		 * Displays appropriate messages for invalid moves, checks, checkmates, and stalemates.
		 * Switches the active player's turn at the end of a valid move.
		 */
		void submitMove(const char*, const char*);


		/**
		 * Returns active colour
		 *
		 * @return active colour as a character
		 */
		char getActiveColour() const;

		/**
		 * Returns active colour as a string
		 *
		 * @return active colour as string
		 */
		string outputActiveColour() const;


		/**
		 * Function to print the board into a 2D array of characters for debugging 
		 * and tracking moves.
		*/
		void printBoard();


	private:

		/* 2D character array representing the chess board */
		Piece* board[8][8]; 

		/* Map structure to generate piece pointers from FEN characters */
		map<char, Piece*> pieceMap;

		/* Stores character denoting whether active colour is black or white */
		char activeColour;

		// Game state variables
		bool inCheckmate = false;
		bool inStalemate = false;

		// Helper functions

		/**
		 * Converts a string representation of piece data to a 2D array of 
		 * Piece pointers on the chess board.
		 * 
		 * @param pieceData A null-terminated string containing piece placement data.
		 * The board is defined to be of size 8x8.
		 * The function modifies the board based on the pieceData input.
		 * Null pointers represent empty spaces on the board.
		*/
		void convertToBoardOfPointers(char*);	


		/**
		 * Checks if the input length of the source and destination squares is valid.
		 *
		 * @param sourceSquare A string representing the source square of the move (e.g., "A2").
		 * @param destSquare A string representing the destination square of the move (e.g., "A4").
		 * @return true if the input lengths are valid (both strings are of length 2), false otherwise.
		 * 
		 * The function verifies that both source and destination squares have a valid input length of 2 characters.
		 */
		bool inputLengthIsValid(const char*, const char*);


		/**
		 * Checks if the specified source and destination squares exist on the chess board.
		 *
		 * @param sourceCol The column character of the source square (e.g., 'A').
		 * @param sourceRow The row character of the source square (e.g., '1').
		 * @param destCol The column character of the destination square (e.g., 'B').
		 * @param destRow The row character of the destination square (e.g., '2').
		 * @return true if both source and destination squares exist on the board, false otherwise.
		 * 
		 * The function verifies if the specified characters for source and destination squares
		 * fall within the valid range for columns ('A' to 'H') and rows ('1' to '8').
		 */
		bool onBoard(char sourceCol, char sourceRow, char destCol, char destRow); 
	

		/**
		 * Switches the active player's turn.
		 *
		 * @param colour The current active player's colour ('w' for White, 'b' for Black).
		 * 
		 * The function updates the active player's colour to switch turns between White and Black.
		 */
		void switchPlayer(char);
		

		// Move processing functions 

		/**
		 * Checks if a chess move is valid according to chess logic and does not put the player's King in check.
		 *
		 * @param sourceRowNo The row index of the source square.
		 * @param sourceColNo The column index of the source square.
		 * @param destRowNo The row index of the destination square.
		 * @param destColNo The column index of the destination square.
		 * @param capture A boolean indicating whether the move involves capturing an opponent's piece.
		 * @return true if the move is valid according to chess logic and does not lead to the player's King being in check, false otherwise.
		 * 
		 * The function first checks if the move is valid according to the piece's specific move logic.
		 * Then, it creates a copy of the board to simulate the move and checks if the move will put the player's King in check.
		 */
		bool moveIsValidAndNotInCheck(int sourceRowNo, int sourceColNo, int destRowNo, int destColNo, bool capture);
		

		/**
		 * Moves a chess piece from the source square to the destination square and handles capturing.
		 *
		 * @param sourceSquare A string representing the source square of the move (e.g., "A2").
		 * @param destSquare A string representing the destination square of the move (e.g., "A4").
		 * 
		 * The function updates the chess board by moving the piece from the source square to the destination square.
		 * If there is a piece at the destination square, it is captured, and the board is updated accordingly.
		 * Outputs the move details to the console.
		 */
		void makeMove(const char*, const char*);		
		

		/**
		 * Checks if a player has any legal moves in response to a check.
		 *
		 * @param playerColour The colour of the player ('w' for White, 'b' for Black).
		 * @return true if the player has at least one legal move to respond to check, false otherwise.
		 * 
		 * The function iterates through the chess board to find all pieces of the specified player's colour
		 * and checks if any of those pieces can make legal moves to respond to a check.
		 */
		bool legalResponse(char);


		/**
		 * Checks if the specified chess piece at the given position can make a valid move.
		 *
		 * @param pieceRow The row index of the chess piece.
		 * @param pieceCol The column index of the chess piece.
		 * @return true if the piece can make at least one valid move, false otherwise.
		 * 
		 * The function iterates through the chess board to determine if the specified piece
		 * can make a valid move to an empty square or capture an opponent's piece without
		 * putting the player's King in check.
		 */
		bool pieceCanMove(int, int);


		/**
		 * Simulates a proposed chess move on a test board.
		 *
		 * @param sourceRow The row index of the source square.
		 * @param sourceCol The column index of the source square.
		 * @param destRow The row index of the destination square.
		 * @param destCol The column index of the destination square.
		 * @param testBoard A 2D array representing the test chess board with Piece pointers.
		 * 
		 * The function creates a copy of the actual board and then simulates the proposed move
		 * on the test board by moving the piece from the source square to the destination square.
		 */	
		void testMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* testBoard[8][8]);
		

		/**
		 * Checks if the specified player's King is in check by opponent's pieces.
		 *
		 * @param playerColour The colour of the player ('w' for White, 'b' for Black).
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @return true if the player's King is in check, false otherwise.
		 * 
		 * The function finds the coordinates of the player's King, then iterates through the chess board
		 * to identify opponent's pieces and checks if any of them can make a valid move towards the King.
		 */
		bool inCheck(char playerColour, Piece* board[8][8]);
		

		/**
		 * Finds the position of the King of a specified colour on a chess board.
		 *
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @param colour The colour of the King to find ('w' for White, 'b' for Black).
		 * @param kingRow Reference to store the row index of the King.
		 * @param kingCol Reference to store the column index of the King.
		 * 
		 * The function iterates through the chess board to find the position of the King of the specified colour.
		 * The result is stored in the provided references `kingRow` and `kingCol`.
		 */
		void findKing(Piece* board[8][8], char, int&, int&);

};

#endif

