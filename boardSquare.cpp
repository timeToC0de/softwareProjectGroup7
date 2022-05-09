// This implementation file is for the board.h. 
// Author: Luke P.
// Created: May 2022, Modified: First Weeks of May 2022.
// Course: SDEV265

#pragma once 
#include <iostream>
#include "boardSquare.h"

const boardSquare& boardSquare::operator=(boardSquare& otherSquare) { // = operator overloaded so that it will allow for a boardSquare to get the same values as another square.
	this->pieceOnSquare = otherSquare.pieceOnSquare;
	this->isWhitePiece = otherSquare.isWhitePiece;
	this->isPieceOn = otherSquare.isPieceOn;

	return *this;
}

const bool boardSquare::operator ==(boardSquare& otherSquare) { // == comparison operator overloaded to check if 2 squares have the same color piece on them.
	return (this->isWhitePiece == otherSquare.isWhitePiece) && (this->isPieceOn == otherSquare.isPieceOn); // Checks to see if the 2 squares both have the same colored pieces on them amd if so, returns true.
};

char boardSquare::toChar() { // prints the piece character that is on the square.
	return this->pieceOnSquare;
}

std::ostream& operator<<(std::ostream& squareOut, boardSquare& info) {
	squareOut << info.pieceOnSquare;
	return squareOut;
}
