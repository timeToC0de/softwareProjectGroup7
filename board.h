/*
* Author(s): Luke P(Original Author), (Add Name here if you contribute(or fork) more to this file).
* Date Created: End of April, 2022.
* Dates Worked on: 5/3/2022, 5/4/2022, 5/5/2022, and(Add date(s) that you modified this file).
* Course: SDEV265.
* 
Header file to Render game board for the chess CLI game.
*/
#pragma once
#include <iostream>
#include <windows.h> // Used for the functions that control the color of the output.
#include <exception> // Used for the exception handling.
//#include <vector>
//#include "piece.h"

// Namespace using statements.
using std::cout;
using std::endl;
using std::cin;


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
	char toChar() {
		return pieceOnSquare;
	}
};

//// Overloaded stream extraction operators used for the boardSquare objects.
//ostream& operator<<(ostream& info, boardSquare& square) {
//	info << square.toChar();
//	return info;
//}

// Row of the board used as the array for the boardSquares.
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
};

// Board which contains the functions to do the rendering of the game board using an array of rows, rows are just arrays of boardSquares.
// I
class board {
#define BSIZE = 8
public:

	const static int bSize = 8; // Board size.
	row chessBoard[bSize]; // Is a dynamic array of rows which are just arrays of boardSquares of size 8.
	HANDLE console_color;  // Creates a HANDLE object, console_color, that will then be passed, along with a color code, to the SetConsoleTextAttribute function to change the console's and text colors as desired by us.
	
						   //vector<row>::iterator chessBoardPtr; // Exploring the idea of using vectors to store the rows.

	void movePiece(int row, int column, char pieceName); // Used to transfer the piece from its current square to the designated square.

	board() { // Default constructor.
		int boardColor;
		initColorHandler(); // Initializes color handler so that it won't be redeclared during every function call.
		
		initBoard(); // Initializes the board so it has the pieces in the appropriate places for the start of the game.
		boardColor = chooseBoardBoundaryColor(); // Prompts user for a color for the board.
		cout << "\n";
		printWhiteBoard(boardColor); // Prints the board based on how it was initialized by the initBoard function.
		
		//for (int i = 0; i < 15; i++) {
		//	cout << "Board Color: " << i << std::endl;
		//	printBoard(i);
		//	cout << "\n";
		//}
		
		cout << "\n";
	}

private:
	void printHorizontalLines(); // Prints the horizontal lines of the game board.
	void printWhiteBoard(int& bColor);
	void printRow(int rowNumber, int borderColor);
	void initBoard(); // Initializes the rank and file arrays that will contain the pieces.
	void initBoardSpot(int row, int column, char pieceCode, bool isWhite, bool isPieceOnArg); // Initializes the boardSpot.
	void changeColorOfText(bool isWhite);
	void initColorHandler();
	int chooseBoardBoundaryColor();
};

// Allows the user to choose the color of the board.
int board::chooseBoardBoundaryColor() {
	int colorChoice; // Stores the color choice of the user.
	bool isValidChoice = false; // Controls input validation loop.
	
	do {
		
		
		cout << "Select the color that you want the board to be:\n"\
			<< "1 - Blue\n"\
			<< "2 - Green\n"\
			<< "3 - Aqua\n"\
			<< "4 - Red\n"\
			<< "5 - Purple\n"\
			<< "6 - Yellow\n"\
			<< "7 - White\n"\
			<< "8 - Gray\n"\
			<< "9 - Light Blue\n"\
			<< "10 - Light Green \n"\
			<< "11 - Light Aqua\n"\
			<< "12 - Light Red\n"\
			<< "13 - Light Purple\n"\
			<< "14 - Light Yellow\n"\
			<< "15 - Bright White\n"\
			<< "Enter one of the color codes: ";

		cin >> colorChoice;

		if (!cin.good()) { // If the user input letters instead of numbers, this exception is thrown.
			cout << "\nOnly input numbers.\n\n";
			cin.clear();			   // Clears the cin error flags.
			cin.ignore(INT_MAX, '\n'); // Clears the input buffer.
		} else if ((colorChoice < 1) || (colorChoice > 15)) { // color choice must be between 1 to 15 or it will throw an exception. ColorChoice may be 1 or 15.
			cout << "\nKeep the number between 1 to 15.\n\n";
		}
		else {
		isValidChoice = true; // Ends the input validation if no exception was thrown.
		}
	} while (!isValidChoice); // Runs until the user has input a valid color code.

	return colorChoice; // Returns int color code.
} // End of chooseBoundary func.

// Used to initialize color handler so that it won't have to be initialized repeatedly in local scope's of functions.
// Lines to change text color obtained then modified from https://www.geeksforgeeks.org/colorizing-text-and-console-background-in-c/?ref=rp
void board::initColorHandler() {
	// Color of the console
	console_color = GetStdHandle(STD_OUTPUT_HANDLE); // This line depends on windows.h so the exact logic of it is unknown to us at this time. It allows the text color to be changed though.
	return;
}

// Prints the Horizontal Boundaries of the board.
void board::printHorizontalLines(){
	int wSize = 33; // number of '-' symbols to be printed for the horizontal line of the board.
	cout << "  ";
	for (int width = 0; width < wSize; width++) {
		cout << "-";
	}
	cout << "\n"; // Newline.
	return;
}

void board::printWhiteBoard(int& bColor) {
	
	char fileLetter = 'A'; // Corresponds to 65 in the ASCII table.
	int rankNumber = 8;    // Not necessary but is useful for clarity.
	
	SetConsoleTextAttribute(console_color, bColor); // Changes the text's color to light yellow to represent the board's borders.
	printHorizontalLines(); // Prints the top horizontal line of the board.
	for (int boardSize = 0; boardSize < 8; boardSize++) { // Prints the rows of the board.
		cout << rankNumber << " "; // Prints Rank number of the row.
		printRow(boardSize, bColor); // Do not let board size be greater than 7 since it will cause a memory access violation or if it doesn't throw an error, it will still cause an out-of-bounds index.
		rankNumber--; // Increments rank by 1.
	}

	for (int fileNum = 0; fileNum < 8; fileNum++) {
		if (fileNum == 0)
			cout << "    " << fileLetter;
		else
			cout << "   " << fileLetter;

		fileLetter++; // Increments fileNumber by one so it will go from A to B to C to D to E to F to G to H.
	}
	return;
}

// Prints the row based on the int value passed to the function.
// Uses the chessBoard vector to print out the appropriate pieces.
void board::printRow(int row, int borderColor) {

	for (int column = 0; column < 8; column++) {
		SetConsoleTextAttribute(console_color, borderColor); // Changes the text's color.
		cout<< "| ";
		changeColorOfText(chessBoard[row].rank[column].isWhitePiece); // Changes the color based on if the current piece's color is dark or light.
		cout << chessBoard[row].rank[column].pieceOnSquare;
		SetConsoleTextAttribute(console_color, borderColor); // Changes back the color so the boundaries aren't colored the same as the pieces unless the user chose that.
		cout << " ";
	}
	SetConsoleTextAttribute(console_color, borderColor); // Changes the text's color to the boundary color.
	cout << "|";
	cout << "\n";
	printHorizontalLines(); // Prints Horizontal line for the bottom of the 
}

void board::changeColorOfText(bool isWhite) { // Changes color of pieces based on their associated "isWhite" boolean value.

	int colorCode; // Variable that contains the color code for the text's color.
	
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
	char pieceCodes[8] = { 'C','N','B', 'Q', 'K', 'B', 'N','C' }; // Used to handle the initBoardSpot.

	for (int r = 0; r < 8; r++) { // Used to traverse from row to row starting at the top row of the board (aka 8th rank all the way to the 1st rank).
		for (int c = 0; c < 8; c++) { // Used to traverse the whole row going from column 1 to column 8 (aka from the 'a' file to the 'h' file).
			
			if (r == 0) { // 8th rank of the board. 
				initBoardSpot(r, c, pieceCodes[c], false, true);  // Black pieces, Used to initialize board squares.
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
				initBoardSpot(r, c, pieceCodes[c], true, true); // White pieces, used to initialize board squares.
			}
			else {
				pieceCode = ' ';
				initBoardSpot(r, c, pieceCode, false, false); // Initializes the empty squares of the board.
			}
			// cout << "Rank: " << r << ", File: " << c << <<", PieceCode: << pieceCode << "\n"; // Used to debug the loops.
		
		} // End of for c
	} // End of for r
} // End of initBoard function.

void board::movePiece(int row, int column, char pieceName) {
	/*
	if(rank[row] == file[column])
	rank[row] = pieceName;
	file[column] = pieceName;*/
 
}

#endif //!H_board

/*
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
					



// Initializes the board to the initial state where all the dark pieces are on the 8th and 7th ranks
// And the light pieces are on the 1st and 2nd ranks.
void board::initBoard() {
	char pieceCode = ' '; // Used as the actual parameter passed to the initBoardPiece function.
	char pieceCodes[8] = { 'C','N','B', 'Q', 'K', 'B', 'N','C' }; // Used to handle the initBoardSpot.

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
} // End of initBoard function.
*/
