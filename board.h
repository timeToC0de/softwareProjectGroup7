/*
* Author(s): Luke P(Original Author), (Add Name here if you contribute(or fork) more to this file).
* Date Created: End of April, 2022.
* Dates Worked on: 5/3/2022, 5/4/2022, 5/5/2022, 5/6/2022, and(Add date(s) that you modified this file).
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
				
	void printInstructionMenu();
	void printPawnInstruction();
	void printRookInstruction();
	void printKnightInstruction();
	void printBishopInstruction();
	void printQueenInstruction();
	void printKingInstruction();
	void printListOfCommands();

	void movePiece(int row, int column, char pieceName); // Used to transfer the piece from its current square to the designated square.

	board() { // Default constructor.
		int boardColor;

		startGame(); // Used to see if the user wants to see a list of rules and instructions for the game.
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
	void startGame(); // Used to prompt the user if they would like to see the instructions.
	void printHorizontalLines(); // Prints the horizontal lines of the game board.
	void printWhiteBoard(int& bColor);
	void printRow(int rowNumber, int borderColor);
	void initBoard(); // Initializes the rank and file arrays that will contain the pieces.
	void initBoardSpot(int row, int column, char pieceCode, bool isWhite, bool isPieceOnArg); // Initializes the boardSpot.
	void changeColorOfText(bool isWhite);
	void initColorHandler();
	int chooseBoardBoundaryColor();
};


// Used to inform the users about the game and to print the initial board.
void board::startGame() {
	int inputCounter = 0; // Used to prevent an infinite loop if the user fails to enter valid input.
	bool isMenuPrinted = false;
	char instructionChoice; // Used to control whether the instructions are printed.

	do {
		cout << "Would you like to view the instructions for the CLI chess game? y/n? ";
		cin >> instructionChoice; // Allows user to enter y or n to display the menu or not.
		inputCounter++; // Keeps track of the number of times that the user has input 
		instructionChoice = tolower(instructionChoice);
		if (instructionChoice == 'y' || instructionChoice == 'n') {
			if (instructionChoice == 'n') {
				return; // Exits the function since user responded no.
			}
			else
				printInstructionMenu(); // Prints the instruction menu.
			isMenuPrinted = true; // Causes input loop to exit.

		}
		else if (inputCounter > 6) { // If the loop runs 5 times or more.
			cout << "Improper input entered 5 times.\n"\
				<< "Program is closing.\n";
			system("pause"); // Pauses so the user can read the message above.
			exit(1); // Exits the program with exit code 1.
		}
		else {
			cout << "Y or N are the only valid options. Please re-enter your choice.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cout << "\n";

	} while (!isMenuPrinted); // Runs until the user enters y or n. May exit if the user fails to enter valid input for 5 iterations.
	return; // Passes control back to calling function.
}

// Prints the instructions.
void board::printInstructionMenu() {
	cout << "\nThis chess game is played turn by turn between 2 players.\n"
		<< "The player with the white pieces moves first.\n"
		<< "Rank is the term for a particular row of the board, and are numbered from 1 to 8.\n"
		<< "File is the term for a column(vertical line of squares) and are labeled a to h.\n"
		<< "To move a piece, input the Piece name, "
		<< "the square the piece is on, and the square that you want the piece to go.\n"
		<< "For example, if you want to move the white pawn on a2 to a4, you would enter Pa2 a4\n"
		<< "Enter the command in all caps or all lowercase, but don't put spaces before or after, only between the two squares.\n"
		<< "You can't move to a square occupied by one of your pieces with any other piece.\n"
		<< "The game board does not have coloring for the white or dark squares because the background colors\n"
		<< "available for the CLI don't mingle well with the color of the 'pieces'.\n\n";
	system("pause"); // Pauses the output so that the previous paragraph will appear and it won't just display the whole instruction set immediately.
	cout << "\nThere are 6 types of pieces, each piece is represented with an abbreviation of their name.\n"
		<< "The pieces for 1 player are 8 Pawns(P), 2 Castles(C), 2 Knights(N), 2 Bishops(B), 1 Queen(Q), and 1 King(K).\n\n";
		printPawnInstruction();
		printRookInstruction();
		printKnightInstruction();
		printBishopInstruction();
		printQueenInstruction();
		printKingInstruction();
	system("pause");
	cout << "\nFinally, I will describe how to win, how to resign, how to draw, what a stalemate is, and castling.\n"
		<< "To win, you must put the other player's king in checkmate.\n"
		<< "Checkmate means that your king or the opposing king is in a square currently being attacked, \n"
		<< "and has no other square to move to that isn't being attacked or occupied by one of your own pieces.\n"
		<< "To resign, instead of a move, enter r into the move prompt.\n"
		<< "To offer a draw, enter d into the move prompt and the opposing player will have the option to \n"
		<< "enter y for yes I accept or n for no I decline the draw.\n"
		<< "If a draw is declined, then the game will resume.\n"
		<< "A stalemate is when one player has no valid moves to make.\n"
		<< "If all pawns are blocking each other and your king is locked in, then that will result in a stalemate.\n"
		<< "Castling can only be done using the king and one of the castles.\n"
		<< "Castling is when you move your king 2 squares towards your rook,\nthe rook will be placed on the square to the other side of the direction of your king's movement.\n"
		<< "Castling can only be done if the king and the particular castle have not yet moved.\n"
		<< "Remember, you can't castle once the King has moved or if the particular rook has moved.\n"
		<< "White's pieces are displayed with the white color and Black's pieces are displayed in gray.\n"
		<< "\nIllegal moves will be rejected and you will be asked to move again.\n"
		<< "To see these rules again during the chess session, simply type i and hit enter.\n\n";
	system("pause");
}

void board::printPawnInstruction() {
	cout << "Pawns may move forward and not backwards. They may move 2 squares forwards if the particular pawn hasn't moved yet.\n"
		<< "Once the pawn has moved, it may only move 1 square forwards at a time.\n"
		<< "Pawns may only take a piece that is 1 square in front of them on one of the 2 adjacent diagonals.\n"
		<< "Pawns may not take the piece directly in front of them.\n"
		<< "Pawns have a special condition called En Passant.\n"
		<< "En Passant is the situation when a pawn is on the 4th rank if the pawn is black\n"
		<< "or the 5th rank if the pawn is white and the opposing player's pawn moves 2 squares landing on the adjacent square\n"
		<< "to your pawn, your pawn may capture this pawn only on the same turn as the opposing player's pawn move.\n"
		<< "After the capture, your pawn will be one rank towards the opposing player's side\nof the board and a square behind where the opposing pawn had just moved.\n"
		<< "Once one of your pawns get across the board to the final rank of the opposing side,\n"
		<< "the pawn will be promoted which means that you may choose it to become a castle, knight, bishop, or queen.\n\n";
}
void board::printRookInstruction() {
	cout << "Castles(aka rooks) are simple, they may move vertically or horizontally up to the square adjacent to one of your pieces.\n"
		<< "If it is an opposing piece, you can have your castle move to their square to capture it if lies on the same rank or file.\n\n";
} 
void board::printKnightInstruction() {
	cout << "The knights are special. They are the only piece that can jump over other pieces.\n"\
		<< "Knights can move in an L shape, that means that they can move to any square\ntwo forwards and one horizontal from their current location.\n"
		<< "They can not land on one of your own pieces though.\n\n";
}
void board::printBishopInstruction() {
	cout << "Bishops are also very simple, they are like castles but they may only move diagonally instead.\n\n";
}
void board::printQueenInstruction() {
	cout << "The Queen is able to move like both the castle and the bishop.\n";
}
void board::printKingInstruction() {
	cout << "The King may move to any square adjacent to his current position.\n"
		<< "The King can't move into check and any particular piece of yours\nis not allowed to make a move resulting in your king being in check.\n\n";
}

void board::printListOfCommands() {
	cout << "The list of command you may enter into the move prompt are: ";
}

// Allows the user to choose the color of the board.
int board::chooseBoardBoundaryColor() {
	int colorChoice; // Stores the color choice of the user.
	bool isValidChoice = false; // Controls input validation loop.
	
	do {
		
		
		cout << "Now select the color that you want the chess board's borders to be:\n"\
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
			<< "14 - Light Yellow\n"
			<< "15 - Bright White\n"
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
