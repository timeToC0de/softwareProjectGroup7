// ChessProject_Group7.cpp : This file contains the 'main' function.
// Authors: Luke P, Jaylameyada T, and Caleb K.
// Date created: 4/23/2022
/* Description: Main program where the chess session is run. */


#include <iostream>
#include <windows.h> // Needed to color the string that represent the pieces.
#include "board.h"
//#include <iomanip> // For tolower() method to convert uppercase to lowercase.

using namespace std;

void startGame();
void printInstructionMenu();
void changeTextColor(HANDLE& consoleColor, int textColorCode);

void printHorizontalLines();

int main()
{
    // Start game.
    board gameBoard;

    // Choose a color.

    // Move pieces.

    //

    return 0;
}
void printHorizontalLines() {

    int wSize = 33; // number of '-' symbols to be printed for the horizontal line of the board.
    for (int width = 0; width < wSize; width++) {
        cout << "-";
    }
    cout << "\n"; // Newline.
    return;
}

// Used to inform the users about the game and to print the initial board.
void startGame() {
    int inputCounter = 0; // Used to prevent an infinite loop if the user fails to enter valid input.
    bool isMenuPrinted = false;
    char instructionChoice; // Used to control whether the instructions are printed.
    cout << "Welcome to the Command Line Interface Chess Game!\n";

    do {
        cout << "Would you like to view the instructions for the CLI chess game? y/n? ";
        cin >> instructionChoice; // Allows user to enter y or n to display the menu or not.
        inputCounter++; // Keeps track of the number of times that the user has input 
        instructionChoice = tolower(instructionChoice);
        if (instructionChoice =='y' || instructionChoice =='n') {
            if (instructionChoice == 'n') {
                return; // Exits the function since user responded no.
            } else
                printInstructionMenu(); // Prints the instruction menu.
            isMenuPrinted = true; // Causes input loop to exit.

        } else if (inputCounter > 6) { // If the loop runs 5 times or more.
            cout << "Improper input entered 5 times.\n"\
                << "program is closing.\n";
            exit(1); // Exits the program with err code 1.
        }
        cout << "\n";

    } while (!isMenuPrinted); // Runs until the user enters y or n. May exit if the user fails to enter valid input for 5 iterations.
    return; // Passes control back to calling function.
}

void printInstructionMenu() {
    cout << "This chess game is played turn by turn between 2 players.\n"\
        << "The player with the white pieces moves first.\n"\
        << "There are 6 types of pieces, each piece is represented with an abbreviation of their name.\n"\
        << ""\
        << "The different pieces for 1 player are 8 pawns, 2 rooks(aka castles), 2 knights, 2 bishops, 1 queen, and 1 king.\n\n"\
        <<"Pawns may move forward and not backwards. They may move 2 squares forwards if the particular pawn hasn't moved yet.\n"\
        <<"";
}

void changeTextColor(HANDLE& consoleColor, int textColorCode) {
    SetConsoleTextAttribute(consoleColor, textColorCode); // Changes the text's color.
}


// Test code section:
/*
* // These are testing different ways to color the game board to represent light and dark squares.

    // Lines to change text color obtained then modified from https://www.geeksforgeeks.org/colorizing-text-and-console-background-in-c/?ref=rp
    // Color of the console
    int colorCode; // Variable that contains the color code for the text's color.
    HANDLE console_color; // Seems to be storing the console_color that will then be passed to the SetConsoleTextAttribute function to change the console and text colors as desired by us, the developers.
    console_color = GetStdHandle(STD_OUTPUT_HANDLE); // This line depends on windows.h so the exact logic of it is unknown to us at this time. It allows the text color to be changed though.
    colorCode = 15; // Changes text color to white.
    changeTextColor(console_color, colorCode); // Changes the text's color.
    cout << "Q\n";

    colorCode = 8; // Changes text color to Grey which represents the dark pieces.
    changeTextColor(console_color, 8); // Changes the text's color.
    cout << "Q\n";
    int col = 2;

    //system("color 70"); // Changes the background to white and the text color to black.
    cout << "Chess Board\n";

    changeTextColor(console_color, 112);
    printHorizontalLines();

    for (int j = 0; j < 8; j++) {

        for (int i = 0; i < 8; i++) {

        switch (i) {
        case 0:
            changeTextColor(console_color, 112);
            cout << "|";
            col = 96;
            changeTextColor(console_color, col);
            cout << "'";
            //col = 241;
            changeTextColor(console_color, col);
            cout << "P";
            //col = 240;
            changeTextColor(console_color, col);

            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";

            break;
        case 1:
            col = 160;
            changeTextColor(console_color, col);
            cout << "`";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";
            break;
        case 2:

            col = 96;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";

            break;
        case 3:
            col = 160;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";

            break;
        case 4:
            col = 96;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";
            break;
        case 5:
            col = 160;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";
            break;
        case 6:
            col = 103;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";
            break;
        case 7:
            col = 167;
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, col);
            cout << "P";
            changeTextColor(console_color, col);
            cout << " ";
            changeTextColor(console_color, 112);
            cout << "|";

            break;
        }

    }
    cout << "\n";
    printHorizontalLines();
    }
    
*/
