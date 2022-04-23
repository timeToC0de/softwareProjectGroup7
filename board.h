/*
Header file to Render game board for the chess CLI game.
*/
#include <iostream>
#pragma once

// Needed to prevent ambiguity to the compiler around definitions of the methods of the class.
#ifndef H_board
#define H_board

class board {

public:
	std::string rank[8]; // AKA rows of the board.
	std::string file[8]; // aka columns of the board.
	void movePiece(int row, int column,std::string pieceName);

private:
	std::string previousRank[8]; // Used to store the previous Rank positions.
	std::string previousFile[8]; // Used to store the previous state of the file positions.
};

void board::movePiece(int row, int column, std::string pieceName) {
	if(rank[row] == file[column])
	rank[row] = pieceName;
	file[column] = pieceName;

}
#endif //!H_board