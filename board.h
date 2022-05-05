/*
* Author(s): Luke Przybyla(Original Author), (Add Name here if you contribute(or fork) more to this file).
* Date Created: End of April, 2022.
* Dates Worked on: 5/3/2022, 5/4/2022, and(Add date(s) that you modified this file).
* Course: SDEV265.
* 
Header file to Render game board for the chess CLI game.
*/
#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "piece.h"

using std::cout;

// Needed to prevent ambiguity to the compiler around definitions of the methods of the classes.
#ifndef H_board
#define H_board

// The boardSquare class is needed to simplify the board's space efficiency since having an array of pieces would mean there would be 64 spots for pieces instead of using data structures that contain only the essential data to do the rendering.
class boardSquare {
public:
	char pieceOnSquare;
	bool isWhitePiece;
	bool isPieceOn;

	boardSquare() {
		pieceOnSquare = ' ';
		isWhitePiece = true;
		isPieceOn = false;
	}
	boardSquare(char pOSq, bool iWPiece, bool isPOn) {
		pieceOnSquare = pOSq;
		isWhitePiece = iWPiece;
		isPieceOn = isPOn;
	}

	const boardSquare& operator=(boardSquare& otherSquare) {
		this->pieceOnSquare = otherSquare.pieceOnSquare;
		this->isWhitePiece = otherSquare.isWhitePiece;
		this->isPieceOn = otherSquare.isPieceOn;

		return *this;
	}
};

// Row functions 
class row {
public:
	boardSquare rank[8]; // rank is the same thing as a row of the board in chess. The rank is a boardSquare array of size 8.

	row() {
		boardSquare initSquare('T', true, true);
		//initSquare.pieceOnSquare = 'T';
		//initSquare.isWhitePiece = true;
		//initSquare.isPieceOn = true;

		for (int r = 0; r < 7; r++) {
			if (r % 2 == 0)
				initSquare.isWhitePiece = false;
			else
				initSquare.isWhitePiece = true;

			rank[r] = initSquare;
		}
	}

	//const boardSquare& operator=(const boardSquare& passedSquare) {
	//	rank[0] = passedSquare;
	//}

	//const linkedListType<Type>& operator=(const linkedListType<Type>& otherList);
};

class board {
#define BSIZE = 8
public:

	const static int bSize = 8;
	row chessBoard[bSize]; // Is a dynamic array(aka vector) of rows which are just string arrays of size 8.
	HANDLE console_color;  // Seems to be storing the console_color that will then be passed to the SetConsoleTextAttribute function to change the console and text colors as desired by us, the developers.
	
						   //vector<row>::iterator chessBoardPtr;

	void movePiece(int row, int column, char pieceName);

	board() {
		// int color2 = 15;
		initColorHandler();
		initBoard();
		for (int i = 0; i < 15; i++) {
			cout << "Board Color: " << i << std::endl;
			printBoard(i);
			cout << "\n";
		}
		
		cout << "\n";
	}

private:
	void printHorizontalLines(); // Prints the horizontal lines of the game board.
	void printBoard(int& bColor);
	void printRow(int rowNumber, int borderColor);
	void initBoard(); // Initializes the rank and file arrays that will contain the pieces.
	void initBoardSpot(int row, int column, char pieceCode, bool isWhite, bool isPieceOnArg); // Initializes the boardSpot.
	void changeColorOfText(bool isWhite);
	void initColorHandler();
};

void board::initColorHandler() {
	// Lines to change text color obtained then modified from https://www.geeksforgeeks.org/colorizing-text-and-console-background-in-c/?ref=rp
	// Color of the console
	console_color = GetStdHandle(STD_OUTPUT_HANDLE); // This line depends on windows.h so the exact logic of it is unknown to us at this time. It allows the text color to be changed though.
	return;
}

// Prints the Horizontal Boundaries of the board.
void board::printHorizontalLines(){
	
	int wSize = 33; // number of '-' symbols to be printed for the horizontal line of the board.
	for (int width = 0; width < wSize; width++) {
		cout << "-";
	}
	cout << "\n"; // Newline.
	return;
}

void board::printBoard(int& bColor) {
	
	//system("color FE");
	SetConsoleTextAttribute(console_color, bColor); // Changes the text's color to light yellow to represent the board's borders.
	printHorizontalLines(); // Prints the top horizontal line of the board.
	for (int boardSize = 0; boardSize < 8; boardSize++) { // Prints the rows of the board.
		printRow(boardSize, bColor);
		//cout << "|";
	}
	return;
}

// Prints the row based on the int value passed to the function.
// Uses the chessBoard vector to print out the appropriate pieces.
void board::printRow(int row, int borderColor) {

	for (int column = 0; column < 8; column++) {
		SetConsoleTextAttribute(console_color, borderColor); // Changes the text's color.
		cout<< "| ";
		changeColorOfText(chessBoard[row].rank[column].isWhitePiece);
		cout << chessBoard[row].rank[column].pieceOnSquare;
		SetConsoleTextAttribute(console_color, borderColor); // Changes the text's color.
		cout << " ";
	}
	SetConsoleTextAttribute(console_color, borderColor); // Changes the text's color to light yellow to represent the board's borders.
	cout << "|";
	cout << "\n";
	printHorizontalLines(); // Prints Horizontal line for the bottom of the 
}

void board::changeColorOfText(bool isWhite) {

	int colorCode; // Variable that contains the color code for the text's color.
	
	//if (isNotAPiece) {  // If the square doesn't have a piece.
	//	colorCode = 15; // Changes the text's color to white.
	//	SetConsoleTextAttribute(console_color, colorCode); // Changes the text's color.
	//	return; // Passes control back to the calling function.
	//}	
	
	if(isWhite) // If the piece is a white piece.
		colorCode = 15; // Changes text color to white.
	else // Else the piece is a black piece.
		colorCode = 8; // Changes text color to Grey which represents the dark pieces.
	SetConsoleTextAttribute(console_color, colorCode); // Changes the text's color.

	return;
}

// Initializes the board spot using the arguments passed to the function.
void board::initBoardSpot(int row, int column, char pieceCode, bool isWhite, bool isPieceOnArg) {
	boardSquare square;
	square.pieceOnSquare = pieceCode;
	square.isWhitePiece = isWhite;
	square.isPieceOn = isPieceOnArg;

	chessBoard[row].rank[column] = square;
	/*chessBoard[row].rank[column].pieceOnSquare = pieceCode;
	chessBoard[row].rank[column].isWhitePiece = isWhite;
	chessBoard[row].rank[column].isPieceOn = isPieceOnArg;*/
	return;
}

// Initializes the board to the initial state where all the dark pieces are on the 8th and 7th ranks
// And the light pieces are on the 1st and 2nd ranks.
void board::initBoard() {
	char pieceCode = ' '; // Used as the actual parameter passed to the initBoardPiece function.

	for (int r = 0; r < 8; r++) { // Used to traverse from row to row starting at the top row of the board (aka 8th rank all the way to the 1st rank).
		for (int c = 0; c < 8; c++) { // Used to traverse the whole row going from column 1 to column 8 (aka from the a file to the h file).
			
			if (r == 0) { // 8th rank of the board.
				// Switch used to initialize board squares. 
				switch (c) {
					case 0: // a file.
						pieceCode = 'C'; // Represents the Castle.
						break;
					case 1: // b file.
						pieceCode = 'N'; // Represents the kNight.
						break;
					case 2: // c file .
						pieceCode = 'B'; // Represents the Bishop.
						break;
					case 3: // d file.
						pieceCode = 'Q'; // Represents the  Queen.
						break;
					case 4: // e file.
						pieceCode = 'K'; // Represents the King.
						break;
					case 5: // f file.
						pieceCode = 'B'; // Represents the Bishop.
						break;
					case 6: // g file.
						pieceCode = 'N'; // Represents the kNight.
						break;
					case 7: // h file.
						pieceCode = 'C'; // Represents the Castle.
						break;
					default:
						cout << "Don't reach this.\n";
				} // End of switch

				initBoardSpot(r, c, pieceCode, false, true);  // Black pieces.

			} // End of if r == 0
			else if (r == 1) { // 7th rank of the board.
				pieceCode = 'P'; // Represents the Pawn.
				initBoardSpot(r, c, pieceCode, false, true);  // Black. 
			}
			else if (r == 6) { // 2nd rank of the board.
				pieceCode = 'P'; // Represents the Pawn.
				initBoardSpot(r, c, pieceCode, true, true);  // White.
			}
			else if (r == 7) { // 1st rank of the board.
				// Switch used to initialize board squares. 
				switch (c) {
				case 0: // a file.
					pieceCode = 'C'; // Represents the Castle.
					break;
				case 1: // b file.
					pieceCode = 'N'; // Represents the kNight.
					break;
				case 2: // c file .
					pieceCode = 'B'; // Represents the Bishop.
					break;
				case 3: // d file.
					pieceCode = 'Q'; // Represents the  Queen.
					break;
				case 4: // e file.
					pieceCode = 'K'; // Represents the King.
					break;
				case 5: // f file.
					pieceCode = 'B'; // Represents the Bishop.
					break;
				case 6: // g file.
					pieceCode = 'N'; // Represents the kNight.
					break;
				case 7: // h file.
					pieceCode = 'C'; // Represents the Castle.   
					break;
				default:
					cout << "Don't reach this.\n";

				}
				initBoardSpot(r, c, pieceCode, true, true); // White pieces.
			}
			else {
				pieceCode = ' ';
				initBoardSpot(r, c, pieceCode, false, false); // Initializes the empty squares of the board.
			}
			// cout << "Rank: " << r << ", File: " << c << <<", PieceCode: << pieceCode << "\n"; // Used to debug the loops.
		} // End of for c
	} // End of for r
}

void board::movePiece(int row, int column, char pieceName) {
	/*
	if(rank[row] == file[column])
	rank[row] = pieceName;
	file[column] = pieceName;*/
 
}


#endif //!H_board
