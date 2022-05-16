/*
* Author(s): Luke P(Original Author), (Add Name here if you contribute(or fork) more to this file).
* Date Created: End of April, 2022.
* Dates Worked on: 5/3/2022, 5/4/2022, 5/5/2022, 5/6/2022, 5/15/2022, 5/16/2022 and(Add date(s) that you modified this file).
* Course: SDEV265.
* 
Header file to Render game board for the chess CLI game.
*/
#pragma once
#include "row.h" // Used for the row class.
//#include <windows.h> // Used for the functions that control the color of the output.

// Needed to prevent ambiguity to the compiler around definitions of the methods of the classes.
#ifndef H_board // Ensures that the directive is not inserted multiple times into a single .cpp file according to Microsoft (https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170)
#define H_board

// Board which contains the functions to do the rendering of the game board using an array of rows, rows are just arrays of boardSquares.
class board {

#define BSIZE = 8
	using con_int = const int; // Type alias
protected:

	con_int static bSize = 8; // Board size.
	row chessBoard[bSize];	  // Is a dynamic array of rows which are just arrays of boardSquares of size 8.
	HANDLE console_color;     // Creates a HANDLE object, console_color, that will then be passed, along with a color code, to the SetConsoleTextAttribute function to change the console's and text colors as desired by us.
	bool isWhitesTurn;	      // This will alternate values and if true, it will cause the board to be printed as the white player's perspective, if false, it will print the board in the black player's perspective.
	int boardColor;			  // Controls board boundary color.	

	void printListOfCommands();
	void printInstructionMenu();
	void printPawnInstruction();
	void printRookInstruction();
	void printKnightInstruction();
	void printBishopInstruction();
	void printQueenInstruction();
	void printKingInstruction();

	bool areBothPiecesSameColor(int firstPieceRow, int& firstPieceColumn, int& secondPieceRow, int& secondPieceColumn); // Used to compare the color of two pieces on the board.
	void movePiece(int& firstRow, int& firstColumn, int& secondRow, int& secondColumn); // Used to transfer the piece from its current square to the designated square.
	void printBoard(int& bColor, bool& isWhiteTurn);

	board() { // Default constructor.
		isWhitesTurn = true;

		startGame(); // Used to see if the user wants to see a list of rules and instructions for the game.
		initColorHandler(); // Initializes color handler so that it won't be redeclared during every function call.
		
		initBoard(); // Initializes the board so it has the pieces in the appropriate places for the start of the game.
		boardColor = chooseBoardBoundaryColor(); // Prompts user for a color for the board.

		//printBoard(boardColor, isWhitesTurn); // Prints the board based on how it was initialized by the initBoard function.
		//std::cout << "\n";
	}

private:
	void startGame(); // Used to prompt the user if they would like to see the instructions.
	void printHorizontalLines(); // Prints the horizontal lines of the game board.
	void printRow(int rowNumber, int borderColor, bool& isWhiteTurn);
	void initBoard(); // Initializes the rank and file arrays that will contain the pieces.
	void initBoardSpot(int row, int column, char pieceCode, bool isWhite, bool isPieceOnArg); // Initializes the boardSpot.
	void changeColorOfText(bool isWhite);
	void initColorHandler();
	int chooseBoardBoundaryColor();
};

#endif //!H_board


// Contains used, old, or potentially useful code.
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
