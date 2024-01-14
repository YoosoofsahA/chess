#include<iostream>
#include<string>
#include<cctype>
#include<cmath>

#include"ChessPieces.h"

using namespace std;

// Implementation of Piece class
Piece::Piece(char _name) {

	pieceName = _name;	

	if (toupper(_name) == _name) {
		pieceColour = 'w';
	}
	else {
		pieceColour = 'b';
	}

	if (pieceColour != 'w' && pieceColour != 'b') {
		cerr << "Not a valid piece" << endl;
	}

}

// Piece destructor
Piece::~Piece() {
}

// Function to get piece name
char Piece::getName() {
	return pieceName;
}

// Function to get piece colour
char Piece::getColour() {
	return pieceColour;
}

// Function to output piece colour
string Piece::outputColour() {
	if (this->pieceColour == 'b') {
		return "Black's ";
	}
	else {
		return "White's ";
	}
}

// Function to set colour of piece
void Piece::setColour(char colour) {
	pieceColour = colour;
}

// Function to check if there are any pieces obstructing a move of any colour in the same column
bool Piece::noColObstruction(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8]) {
	
	int rankLow = (sourceRow < destRow) ? sourceRow : destRow;
	int rankHigh = (sourceRow < destRow) ? destRow : sourceRow;

	for (int i = rankLow + 1; i < rankHigh; i++) {
		if (board[i][sourceCol]) {
			return false;
		}
	}
	return true;
}

// Function to check if there are any pieces obstructing a move of any colour in the same row
bool Piece::noRowObstruction(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8]) {
	
	int colLow = (sourceCol < destCol) ? sourceCol : destCol;
	int colHigh = (sourceCol < destCol) ? destCol : sourceCol;

	for (int i = colLow + 1; i < colHigh; i++) {
		if (board[sourceRow][i]) {
			return false;
		}
	}
	return true;
}

// Function to check if there are any pieces obstructing a move of any colour in the same diagonal
bool Piece::noDiagonalObstruction(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8]) {

	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	int colLow = (sourceCol < destCol) ? sourceCol : destCol;
	int colHigh = (sourceCol < destCol) ? destCol : sourceCol;

	// Check through all squares in the four possible diagonal directions
	for (int i = 1; i < (colHigh - colLow); i++) {
			if (rowChange > 0 && colChange > 0) {
			if (board[sourceRow + i][sourceCol + i]) {
				return false;
			}
		}
		if (rowChange > 0 && colChange < 0) {
			if (board[sourceRow + i][sourceCol - i]) {
				return false;
			}
		}
		if (rowChange < 0 && colChange > 0) {
			if (board[sourceRow - i][sourceCol + i]) {
				return false;
			}
		}
		if (rowChange < 0 && colChange < 0) {
			if (board[sourceRow - i][sourceCol - i]) {
				return false;
			}
		}	
	}
	
	return true;
}

/* ---------------------------------------------------------------------- */

// Implementation of King class
King::King(char _name) : Piece(_name) {
}

King::~King() {
}

string King::outputName() {
	return "King";
}

/**
 * King can only move:
 * - One square in any direction
 */
bool King::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {

	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	// King can only move one square in any direction
	if (abs(rowChange) < 0 || abs(rowChange) > 1) {
		return false;
	}

	if (abs(colChange) < 0 || abs(colChange) > 1) {
		return false;
	}

	return true;
}

/* ---------------------------------------------------------------------- */

// Implementation of Queen class
Queen::Queen(char _name) : Piece(_name) {
}

Queen::~Queen() {
}

string Queen::outputName() {
	return "Queen";
}

/**
 * Queen can only move:
 * - Any number of squares along row or column or diagonal
 * - Cannot move if there are pieces blocking
 */
bool Queen::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {

	// Create pointers to Rook and Bishop of same colour as Queen to simulate Queen
	Rook* rook = new Rook('R');
	Bishop* bishop = new Bishop('B');

	rook->setColour(this->pieceColour); 
	bishop->setColour(this->pieceColour);

	// If valid moves for either Rook or Bishop then valid moves for Queen
	if ((rook->validMove(sourceRow, sourceCol, destRow, destCol, board, capture)) || (bishop->validMove(sourceRow, sourceCol, destRow, destCol, board, capture))) {
			delete rook;
			delete bishop;

			return true;
	}		

	delete rook;
	delete bishop;

	return false;
}

/* ---------------------------------------------------------------------- */

// Implementation of Bishop class
Bishop::Bishop(char _name) : Piece(_name) {
}

Bishop::~Bishop() {
}

string Bishop::outputName() {
	return "Bishop";
}

/**
 * Bishop can only move:
 * - Diagonally in any direction
 * - If there are no pieces blocking it
 */
bool Bishop::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {
	
	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	// Bishop can only move diagonally - i.e. absolute row movement and column movement are equal
	if (abs(rowChange) != abs(colChange)) {
		return false;
	}
	// Bishop cannot move if there are pieces of any colour blocking it
	if (!noDiagonalObstruction(sourceRow, sourceCol, destRow, destCol, board)) {
		return false;
	}

	// Cannot move if there is a piece of the same colour in destination square
	if (board[destRow][destCol]) {
		if (this->getColour() == board[destRow][destCol]->getColour()) {
			return false;
		}
	}

	return true;
}

/* ---------------------------------------------------------------------- */

// Implementation of Rook class
Rook::Rook(char _name) : Piece(_name) {
}

Rook::~Rook() {
}

string Rook::outputName() {
	return "Rook";
}

/**
 * Rook can only move:
 * - Only along same rank or same file for any number of squares
 * - If there are no pieces blocking it
 */
bool Rook::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {
	
	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	// Rook moves along the same row (i.e. column position changes but row does not)
	if (abs(colChange) > 0 && rowChange != 0) {
		return false;
	}
	// Rook only moves along row if there are no obstructions
	if (!noColObstruction(sourceRow, sourceCol, destRow, destCol, board)) {
		return false;
	}	
	
	// Rook moves along the same column (i.e. row changes but column does not)
	if (abs(rowChange) > 0 && colChange != 0) {
		return false;
	}
	// Rook only moves along column if there are no obstructions
	if (!noRowObstruction(sourceRow, sourceCol, destRow, destCol, board)) {
		return false;
	}

	// Cannot move if there is a piece of the same colour in destination square
	if (board[destRow][destCol]) {
		if (this->getColour() == board[destRow][destCol]->getColour()) {
			return false;
		}
	}	

	return true;
}

/* ---------------------------------------------------------------------- */

// Implementation of Knight class
Knight::Knight(char _name) : Piece(_name) {
}

Knight::~Knight() {
}

string Knight::outputName() {
	return "Knight";
}

/**
 * Knight only moves:
 * - Two squares vertically and one square horizontally
 * - Two squares horizontally and one square vertically
 * - Can move with obstacles in the way
 */
bool Knight::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {

	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	// Can only move in an L-shape
	if (!((abs(rowChange) * abs(colChange)) == 2)) {
		return false;
	}

	// Cannot move if there is a piece of the same colour in destination square
	if (board[destRow][destCol]) {
		if (this->getColour() == board[destRow][destCol]->getColour()) {
			return false;
		}
	}
	
	return true;
}

/* ---------------------------------------------------------------------- */

// Implementation of Pawn class
Pawn::Pawn(char _name) : Piece(_name) {
}

Pawn::~Pawn() {
}

string Pawn::outputName() {
	return "Pawn";
}

/**
 * Pawn can only move:
 *	- Forward 1 square
 *	- Forward 2 squares if first move
 *	- Only move diagonally forward one square when capturing a piece of the opposite colour
 *	- If there are no pieces blocking it 
 */
bool Pawn::validMove(int sourceRow, int sourceCol, int destRow, int destCol, Piece* board[8][8], bool capture) {

	// Calculate how the pawn wants to move
	int rowChange = destRow - sourceRow;
	int colChange = destCol - sourceCol;

	// Absolute value for pawn movement forwards in column
	int pawnForwardMove = 0; 
	if (this->getColour() == 'w') {
		pawnForwardMove = -rowChange;
	}
	else if (this->getColour() == 'b'){
		pawnForwardMove = rowChange;
	}

	// When capturing - Pawn can only move diagonally
	if (capture) {
		if (pawnForwardMove != 1 || abs(colChange) != 1) {
			return false;
		}
		return true;
	}

	// When not capturing 
	
	// Cannot move forwards if there is a piece in destination square
	if (board[destRow][destCol]) {
			return false;
	}
	// Pawn can only move vertically and forward at least 1 square
	if (abs(colChange) != 0 || pawnForwardMove < 1) {
		return false;
	}
	// If it does move forward can only move 1 or 2 squares
	if (pawnForwardMove > 2) {
		return false;
	}
	// Can only move two squares when at the start
	if (!pawnAtStart(sourceRow)) {
		if (pawnForwardMove == 2) {
			return false;
		}
	}
	// Can only move forwards two squares if there is no piece obstructing it
	if (pawnForwardMove == 2) {
		if (!noColObstruction(sourceRow, sourceCol, destRow, destCol, board)) {
			return false;
		}
	}
	return true;
}

// Defines if pawn is at starting position 
bool Pawn::pawnAtStart(int sourceRow) {

	if (this->getColour() == 'w') {
		if (sourceRow == 6) {
			return true;
		}
	}
	if (this->getColour() == 'b') {
		if (sourceRow == 1) {
			return true;
		}
	}
	return false;
}

