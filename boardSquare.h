#pragma once

#ifndef H_boardSquare
#define H_boardSquare

// The boardSquare class is needed to simplify the board's space efficiency since having an array of pieces would mean there would be 64 spots for pieces instead of using data structures that contain only the essential data to do the rendering.
class boardSquare {
public:
	char pieceOnSquare; // Contains the char that designates a particular piece.
	bool isWhitePiece;  // Needed to distinguish what piece is on the square.
	bool isPieceOn;		// Stores whether the square is occupied.

	boardSquare() {
		pieceOnSquare = ' ';
		isWhitePiece = false;
		isPieceOn = false;
	}
	boardSquare(char pOSq, bool iWPiece, bool isPOn) {
		pieceOnSquare = pOSq;
		isWhitePiece = iWPiece;
		isPieceOn = isPOn;
	}

	const boardSquare& operator=(boardSquare& otherSquare);

	const bool operator ==(boardSquare& otherSquare);

    char toChar();

	friend std::ostream& operator<<(std::ostream& squareOut, boardSquare& info);
};
#endif // !H_boardSquare