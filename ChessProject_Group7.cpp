// ChessProject_Group7.cpp : This file contains the 'main' function.
// Authors: Luke P, Jaylameyada T, and Caleb K.
// Date created: 4/23/2022
/* Description: Main program where the chess session is run. */

#include <iostream>
#include <windows.h> // Needed to color the string that represent the pieces.
#include "board.h"
//#include <iomanip> // For tolower() method to convert uppercase to lowercase.

using namespace std;

void printInstructionMenu(); // Prints instructions.
void changeTextColor(HANDLE& consoleColor, int textColorCode);

//void printHorizontalLines();

int main()
{
    bool isGameNotEnded = true;
    cout << "Welcome to the Command Line Interface Chess Game!\n\n";
    // Start game.
    board gameBoard;

    do { // Chess Game loop.
        if (isGameNotEnded) {
            isGameNotEnded = false; // False, game is now ended.
        }
    // Move pieces.

    } while (isGameNotEnded);

   HANDLE consoleClr;
   consoleClr = GetStdHandle(STD_OUTPUT_HANDLE);
   int colorCode = 7; // 7 Prints a black background and text colored white.
   changeTextColor(consoleClr, colorCode); // Changes text so the final lines will be in the standard black and white color.

    return 0;
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
