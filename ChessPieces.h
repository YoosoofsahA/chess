#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <string>
using namespace std;

class Piece {
	protected:
		char pieceColour;
		char pieceName;


		/**
		 * Checks if there are no pieces obstructing a move in the same column.
		 *
		 * @param sourceRow The row index of the source square.
		 * @param sourceCol The column index of the source square.
		 * @param destRow The row index of the destination square.
		 * @param destCol The column index of the destination square.
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @return true if there are no obstructions, false otherwise.
		 */
		bool noColObstruction(int, int, int, int, Piece* board [8][8]);
		

		/**
		 * Checks if there are no pieces obstructing a move in the same row.
		 *
		 * @param sourceRow The row index of the source square.
		 * @param sourceCol The column index of the source square.
		 * @param destRow The row index of the destination square.
		 * @param destCol The column index of the destination square.
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @return true if there are no obstructions, false otherwise.
		 */		
		bool noRowObstruction(int, int, int, int, Piece* board [8][8]);
		
		
		/**
		 * Checks if there are no pieces obstructing a move in the same diagonal.
		 *
		 * @param sourceRow The row index of the source square.
		 * @param sourceCol The column index of the source square.
		 * @param destRow The row index of the destination square.
		 * @param destCol The column index of the destination square.
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @return true if there are no obstructions, false otherwise.
		 */		
		bool noDiagonalObstruction(int, int, int, int, Piece* board [8][8]);

	public:
		
		/**
		 * Constructor for the Piece class.
		 *
		 * @param _name The character representing the name of the piece.
		 * 
		 * Initializes a Piece object with the specified name and determines its colour ('w' for White, 'b' for Black).
		 * Displays an error message if the provided name is not valid.
		 */
		Piece(char);


		/**
		 * Virtual Piece class destructor
		*/
		virtual ~Piece();


		/**
		 * Gets the name of the piece.
		 *
		 * @return The character representing the name of the piece.
		 */
		char getName();


		/**
		 * Gets the colour of the piece.
		 *
		 * @return The character representing the colour of the piece ('w' for White, 'b' for Black).
		 */
		char getColour();
		

		/**
		 * Outputs the colour of the piece as a string.
		 *
		 * @return A string representing the colour of the piece ("Black's " or "White's ").
		 */
		string outputColour();


		/**
		 * Sets colour of piece
		 * 
		 * @param colour Colour to set pieceColour to
		*/
		void setColour(char);


		/**
		 * Pure virtual function to output the name of the piece as a string.
		 *
		 * @return A string representing the name of the piece.
		 * 
		 * This function must be implemented by the derived classes to provide specific names for each type of chess piece.
		 */
		virtual string outputName() = 0;


		/**
		 * Pure virtual function to check if a move is valid for the specific type of chess piece.
		 *
		 * @param sourceRow The row index of the source square.
		 * @param sourceCol The column index of the source square.
		 * @param destRow The row index of the destination square.
		 * @param destCol The column index of the destination square.
		 * @param board A 2D array representing the chess board with Piece pointers.
		 * @param capture A boolean indicating whether the move involves capturing an opponent's piece.
		 * @return true if the move is valid, false otherwise.
		 * 
		 * This function must be implemented by the derived classes to define the specific movement rules for each type of chess piece.
		 */
		virtual bool validMove(int, int, int, int, Piece*[8][8], bool) = 0;

};

// Declaration of individual piece inherited classes


/**
 * King class, derived from the Piece class.
 * 
 * The King class represents the King chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the King's constructor, destructor, outputName,
 * and validMove functions.
 */
class King : public Piece {
	public:
		King(char);
		~King() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
		
};


/**
 * Queen class, derived from the Piece class.
 * 
 * The Queen class represents the Queen chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the Queen's constructor, destructor, outputName,
 * and validMove functions.
 */
class Queen : public Piece {
	public:
		Queen(char);
		~Queen() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
};


/**
 * Bishop class, derived from the Piece class.
 * 
 * The Bishop class represents the Bishop chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the Bishop's constructor, destructor, outputName,
 * and validMove functions.
 */
class Bishop : public Piece {
	public:
		Bishop(char);
		~Bishop() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
};


/**
 * Rook class, derived from the Piece class.
 * 
 * The Rook class represents the Rook chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the Rook's constructor, destructor, outputName,
 * and validMove functions.
 */
class Rook : public Piece {
	public:
		Rook (char);
		~Rook() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
};


/**
 * Knight class, derived from the Piece class.
 * 
 * The Knight class represents the Knight chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the Knight's constructor, destructor, outputName,
 * and validMove functions.
 */
class Knight : public Piece {
	public:
		Knight(char);
		~Knight() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
};


/**
 * @brief Pawn class, derived from the Piece class.
 * 
 * The Pawn class represents the Pawn chess piece, inheriting from the Piece base class.
 * It provides specific implementations for the Pawn's constructor, destructor, outputName,
 * validMove, and a private helper function pawnAtStart.
 */
class Pawn : public Piece {
	public:
		Pawn(char);
		~Pawn() override;
		string outputName() override;
		bool validMove(int, int, int, int, Piece*[8][8], bool) override;
	
	private:
    
	/**
     * Checks if the pawn is at its starting position.
     *
     * @param sourceRow The current row index of the pawn.
     * @return true if the pawn is at its starting position, false otherwise.
     * This private helper function is used to determine if the pawn can make a two-square move.
     */	
		bool pawnAtStart(int);
};

#endif

