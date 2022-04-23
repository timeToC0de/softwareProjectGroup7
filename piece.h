#pragma once

#ifndef H_piece
#define H_piece

class pieces {
public:

	pieces(int row, int column, bool isWhite) {}; // Default Constructor.

protected:

	int position[2]; // Used to store the position of the piece. The 1st spot of the arr is row(rank) and 2nd is column(file).
	char pieceCode[2]; // Used to store the abbreviation of the piece.
	bool isAWhitePiece; // Used to control how the piece is colored when the game board is rendered.
};

pieces::pieces(int row, int column, bool isWhite) {
	position[0] = row;
	position[1] = column;
	isAWhitePiece = isWhite;
}
#endif // !H_piece