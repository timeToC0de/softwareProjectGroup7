#pragma once
#include "boardSquare.h"

#ifndef H_row
#define H_row

// Row of the board used as the array for the boardSquares.
class row {
public:
	boardSquare rank[8]; // rank is the same thing as a row of the board in chess. The rank is a boardSquare array of size 8.

	row() {
		boardSquare initSquare('T', true, true); // Initializes boardSquare.

		for (int r = 0; r < 7; r++) { // Initializes whole row to contain basic boardSquare.
			if (r % 2 == 0)
				initSquare.isWhitePiece = false;
			else
				initSquare.isWhitePiece = true;

			rank[r] = initSquare;
		}
	}
};

#endif // !H_row.