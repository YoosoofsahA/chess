#include <iostream>
#include <map>
#include <cctype>
#include <cstring>
#include <string>

#include "ChessBoard.h"
#include "ChessPieces.h"

using namespace std;

// ChessBoard class implementation

/* Base constructor definition */
ChessBoard::ChessBoard() {

	// Create map of char inserts and Piece pointers
	pieceMap.insert(make_pair('K', new King('K')));
	pieceMap.insert(make_pair('Q', new Queen('Q')));
	pieceMap.insert(make_pair('B', new Bishop('B')));
	pieceMap.insert(make_pair('R', new Rook('R')));
	pieceMap.insert(make_pair('N', new Knight('N')));
	pieceMap.insert(make_pair('P', new Pawn('P')));
	pieceMap.insert(make_pair('k', new King('k')));
	pieceMap.insert(make_pair('q', new Queen('q')));
	pieceMap.insert(make_pair('b', new Bishop('b')));
	pieceMap.insert(make_pair('r', new Rook('r')));
	pieceMap.insert(make_pair('n', new Knight('n')));
	pieceMap.insert(make_pair('p', new Pawn('p')));

}

/* ChessBoard destructor */
ChessBoard::~ChessBoard() {

	for (auto it = pieceMap.begin(); it != pieceMap.end(); it++) {
		Piece* ptr = it->second;
		delete ptr;
	}

	pieceMap.clear();
}

/* Returns active colour character */
char ChessBoard::getActiveColour() const {
	return activeColour;
}

/* Returns active colour string */
string ChessBoard::outputActiveColour() const {
	if (activeColour == 'w') {
		return "White's ";
	}
	return "Black's ";
}

/* Definition of loadState which converts FEN notation into 2D array of piece pointers */
void ChessBoard::loadState(const char* boardState) {

	int whiteSpace = 0;

	char pieceData[64];

	int i = 0;
	while (boardState[i] != '\0') {
		if (boardState[i] == ' ') {
			whiteSpace++;
		}
		if (whiteSpace == 0) {
			pieceData[i] = boardState[i];
			pieceData[i + 1] = '\0';
		}
		if (whiteSpace == 1) {
			i++;
			activeColour = boardState[i];
		}
		i++;
	}

	// Convert string into chess board of piece pointers
	convertToBoardOfPointers(pieceData);

	cout << "A new board state is loaded!" << endl;

}

// Function to convert the piece data into an array of Piece pointers
void ChessBoard::convertToBoardOfPointers(char* pieceData) {

	int row = 0;
	int col = 0;

	// Loop through piece data and create pointers
	int i = 0;
	while (pieceData[i] != '\0' && row < 8) {

		if (pieceData[i] == '/') {
			i++;
			row++;
			col = 0;
		}
		if (pieceData[i] >= '1' && pieceData[i] <= '8') {
			int noEmptySpaces = pieceData[i] - '0';
			for (int i = 0; i < noEmptySpaces; i++) {
					board[row][col] = nullptr; // Spaces = null pointers
				col++;
			}
			i++;
		}
		else {
			board[row][col] = pieceMap[pieceData[i]];
			col++;
			i++;
		}
	}
}

// Function used in debugging to test moves
void ChessBoard::printBoard() {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			
			if (!board[i][j]) {
				cout << " ";
			}
			else {
				cout << board[i][j]->getName();
			}

		}
		cout << "\n";
	}
	cout << "\n";
}

// Function used to submit a move from source square to destination square
void ChessBoard::submitMove(const char* sourceSquare, const char* destSquare) {

	// Check if the game is already over
	if (inCheckmate) {
		cout << "The game already ended in checkmate!" << endl;
		return;
	}
	if (inStalemate) {
		cout << "The game already ended in stalemate!" << endl;
		return;
	}

	// Create variables for source and destination row and column
	char sourceCol = sourceSquare[0];
	char sourceRow = sourceSquare[1];
	char destCol = destSquare[0];
	char destRow = destSquare[1];

	// Convert characters to integer indices 0-7
	int sourceColNo = sourceCol - 'A';
	int sourceRowNo = '8' - sourceRow;
	int destColNo = destCol - 'A';
	int destRowNo = '8' - destRow;

	// Set boolean for piece being captured
	bool capture = false;

	// Pointers to pieces / null for source and destination squares
	Piece* currentPiece = board[sourceRowNo][sourceColNo];
	Piece* destPiece = board[destRowNo][destColNo];

	// Check input character length is valid
	if (!inputLengthIsValid(sourceSquare, destSquare)) {
		cout << "Input sqaure string entry invalid" << endl;
		return;
	}

	// Check source and destination squares are on the board
	if (!onBoard(sourceCol, sourceRow, destCol, destRow)) {
		cout << "Input squares are not on the board" << endl;
		return;
	}	

	// Check there is a piece in the source square
	if (!currentPiece) {
		cout << "There is no piece at position " << sourceSquare << "!" << endl;
		return;
	}

	// Check if source and destinations squares are the same
	if (sourceRow == destRow && sourceCol == destCol) {
		cout << "Cannot submit move to the same square!" << endl;
		return;
	}

	// Check that the correct colour piece is being moved for this turn	
	if (currentPiece->getColour() != activeColour) {
		cout << "It is not ";
		if (activeColour == 'w') {
			cout << "Black's ";
		}
		else {
			cout << "White's ";
		}
		cout << "turn to move!" << endl;
		return;
	}

	// Check that source piece and destination pieces are not the same colour 
	// if not then set capture to true as moving to a square with opponent's piece 
	if (destPiece) {
		if (destPiece->getColour() == currentPiece->getColour()) {
			cout << this->outputActiveColour() << currentPiece->outputName() << " cannot move to " << destSquare << "!" << endl;
			return;
		}
		capture = true;
	}

	// Checks if piece at source square can move in line with logic
	// and checks if move will lead to player being in check - as if it does it is illegal
	if (moveIsValidAndNotInCheck(sourceRowNo, sourceColNo, destRowNo, destColNo, capture)) {

		// If move is possible and doesn't put the king in check then make the move
		makeMove(sourceSquare, destSquare);
	
		// After move was made check if the move puts the opponent's King in check
		char opponentColour = (activeColour == 'w' ? 'b' : 'w');
		string opponent = (opponentColour == 'w' ? "White " : "Black ");

		if (inCheck(opponentColour, board)) {
				
			// If opponenet King in check and opponent has no response to check then checkmate
			if (!legalResponse(opponentColour)) {
				cout << opponent << "is in checkmate" << endl;
				inCheckmate = true;
				return;
			}
			else {
				// If in check and there is a legal response then opponent is just in check
				cout << opponent << "is in check" << endl;
			}
		}
		else {
			// If not in check and no legal response then opponent is in stalemate
			if (!legalResponse(opponentColour)) {
				cout << "Game is in stalemate" << endl;
				inStalemate = true;
				return;
			}
		}
	}
	else {
		// Otherwise move is not valid
		cout << this->outputActiveColour() << currentPiece->outputName()
		 << " cannot move to " << destSquare << "!" << endl;
	}

	// At the end of the turn switch colour of active player
	switchPlayer(activeColour);
}

// Checks that moves follows chess logic and does not put player's King in check
bool ChessBoard::moveIsValidAndNotInCheck(int sourceRowNo, int sourceColNo, int destRowNo, int destColNo, bool capture) {
	
	Piece* currentPiece = board[sourceRowNo][sourceColNo];
	char pieceColour = currentPiece->getColour();

	// Check that the piece can move from source to destination according to logic
	if (currentPiece->validMove(sourceRowNo, sourceColNo, destRowNo, destColNo, board, capture)) {

		// Create a copy of the board to simulate the move
		Piece* testBoard[8][8];
		testMove(sourceRowNo, sourceColNo, destRowNo, destColNo, testBoard);

		// See if the move will put active player's King in check
		if(inCheck(pieceColour, testBoard)) {
			return false;
		}

		// Move is valid logically and does not lead to check
		return true;
	}

	// Move is not valid logically
	return false;
}

// Checks if player has any legal moves in response to check
bool ChessBoard::legalResponse(char playerColour) {

	// Loop through board to get all player pieces
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Piece* piece = board[row][col];

			if (piece != NULL && piece->getColour() == playerColour) {
				// See if player's pieces can make any legal moves

				if (pieceCanMove(row, col)) {
					return true;
				}
			}
		}
	}
	// No player piece can make any legal moves
	return false;
}

// Check if player piece can make any legal moves
bool ChessBoard::pieceCanMove(int pieceRow, int pieceCol) {

	char pieceColour = board[pieceRow][pieceCol]->getColour();
	char opponentColour = (pieceColour == 'w' ? 'b' : 'w');

	// Loop through the board to see if specified piece can make a valid move
	for (int destRow = 0; destRow < 8; destRow++) {
		for (int destCol = 0; destCol < 8; destCol++) {
			Piece* dest = board[destRow][destCol];

			// Move to empty square or opponent piece
			if (!dest || dest->getColour() == opponentColour) {
				
				// Capture opponent piece if it exists
				bool capture = (dest == NULL ? false : true);	

				if (moveIsValidAndNotInCheck(pieceRow, pieceCol, destRow, destCol, capture)) {
					return true;
				}
			}
		}
	}
	// Selected piece has no valid moves where the King is not in check
	return false;
}

// Moves source piece to destination square and handles capturing
void ChessBoard::makeMove(const char* sourceSquare, const char* destSquare) {

	// Create variables for source and destination row and column
	char sourceCol = sourceSquare[0];
	char sourceRow = sourceSquare[1];
	char destCol = destSquare[0];
	char destRow = destSquare[1];

	// Convert characters to integer indices 0-7
	int sourceColNo = sourceCol - 'A';
	int sourceRowNo = '8' - sourceRow;
	int destColNo = destCol - 'A';
	int destRowNo = '8' - destRow;

	// Piece pointers to source, destination and captured piece if relevant
	Piece* sourcePiece = board[sourceRowNo][sourceColNo];
	Piece* capturedPiece = nullptr;
	
	string capturedName;
	string capturedColour;

	// If there is a piece to be captured - handle capturing
	if (board[destRowNo][destColNo]) {
		// Destination piece is captured
		capturedPiece = board[destRowNo][destColNo];		
		capturedName = capturedPiece->outputName();
		capturedColour = capturedPiece->outputColour();

		board[destRowNo][destColNo] = board[sourceRowNo][sourceColNo]; // Move source piece
		board[sourceRowNo][sourceColNo] = nullptr;
		 
	}
	// Else if there is no piece to be captured, move source piece to destination square
	else {
		// Move source piece to destination square and make source square empty
		board[destRowNo][destColNo] = board[sourceRowNo][sourceColNo]; // Move source piece
		board[sourceRowNo][sourceColNo] = nullptr;
	}

	// Output scenarios
	if (capturedPiece) {
		cout << sourcePiece->outputColour() << sourcePiece->outputName()
		 << " moves from " << sourceSquare << " to " << destSquare << " taking "
		 << capturedColour << capturedName << endl; 
	}
	else {
		cout << sourcePiece->outputColour() << sourcePiece->outputName()
		 << " moves from " << sourceSquare << " to " << destSquare << endl;
	}

}

// Checks if specified colour's King is in check by opponent's pieces
bool ChessBoard::inCheck(char playerColour, Piece* board[8][8]) {

	int kingRow;
	int kingCol;

	bool capture = true;

	// Gets the coordinates of the King square
	findKing(board, playerColour, kingRow, kingCol);

	// Set opposition colour
	char oppColour = (playerColour == 'w' ? 'b' : 'w');

	// Loop through each square of the board and identify opponent's pieces
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Piece* piece = board[row][col];

			// Identify opponent's pieces
			if (piece != NULL && piece->getColour() == oppColour) {
				// Check if opponents piece can move towards the King
				if (piece->validMove(row, col, kingRow, kingCol, board, capture)) {
					// If move is possible then King is in check
					return true;
				}
			}
		}
	}
	// King is not in check
	return false;
}

// Simulates a proposed move on a test board
void ChessBoard::testMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* testBoard[8][8]) {

	// Make testBoard a copy of the actual board
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			testBoard[row][col] = board[row][col];
		}
	}
	// Make the simulated move on the test board
	testBoard[destRow][destCol] = testBoard[sourceRow][sourceCol];
	testBoard[sourceRow][sourceCol] = nullptr;
}

// Returns position of the king of a specified colour
void ChessBoard::findKing(Piece* board[8][8], char colour, int& kingRow, int& kingCol) {

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board[row][col]) {
				if (colour == 'w') {
					if (board[row][col]->getName() == 'K') {
						kingRow = row;
						kingCol = col;
					}
				}
				if (colour == 'b') {
					if (board[row][col]->getName() == 'k') {
						kingRow = row;
						kingCol = col;
					}
				}
			}
		}
	}

}

// Switches active player
void ChessBoard::switchPlayer(char colour) {
	if (colour == 'w') {
		this->activeColour = 'b';
	}
	else {
		this->activeColour = 'w';
	}
}

// Checks input length of string is valid
bool ChessBoard::inputLengthIsValid(const char* sourceSquare, const char* destSquare) {
	
	if (strlen(sourceSquare) != 2 || strlen(destSquare) != 2) {
		return false;
	}
	return true;
}

// Checks square exists on the board
bool ChessBoard::onBoard(char sourceCol, char sourceRow, char destCol, char destRow) {

	if (sourceCol < 'A' || sourceCol > 'H' || 
			sourceRow < '1' || sourceRow > '8' || 
			destCol < 'A' || destCol > 'H' || 
			destRow < '1' || destRow > '8') {
			return false;
		}
	return true;
}
