chess: ChessMain.o chess.o pieces.o
	g++ -Wall -g ChessMain.o chess.o pieces.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

chess.o: chess.cpp ChessBoard.h ChessPieces.h
	g++ -Wall -g -c chess.cpp

pieces.o: pieces.cpp ChessPieces.h
	g++ -Wall -g -c pieces.cpp

clean:
	rm -f *.o chess
