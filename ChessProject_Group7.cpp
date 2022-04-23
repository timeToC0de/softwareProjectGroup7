// ChessProject_Group7.cpp : This file contains the 'main' function.
// Author: Luke Przybyla, Jaylameyada M. Taylor, and Caleb Kumpf.
// Date Due 4/23/2022
/* Description: Main program where the chess session is run. */

#include <iostream>
#include <windows.h> // Needed to color the string that represent the pieces.
//#include <iomanip> // For tolower() method to convert uppercase to lowercase.

using namespace std;

void startGame();
void printInstructionMenu();
void changeTextColor(HANDLE& consoleColor, int textColorCode);

int main()
{
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


    // Start game.

    // Choose a color.

    // Move pieces.

    //

    return 0;
}

// Used to inform the users about the game and to print the initial board.
void startGame() {
    int inputCounter = 0; // Used to prevent an infinite loop if the user fails to enter valid input.
    bool isMenuPrinted = true;
    char instructionChoice; // Used to control whether the instructions are printed.
    cout << "Welcome to the Command Line Interface Chess Game!\n";

    do {
        cout << "Would you like to view the instructions for the CLI chess game? y/n? ";
        cin >> instructionChoice; // Allows user to enter y or n to display the menu or not.
        inputCounter++;
        instructionChoice = tolower(instructionChoice);
        if (instructionChoice =='y') {
            printInstructionMenu();

        } else if (inputCounter > 6) { // If the loop runs 5 times or more.
            cout << "Improper input entered 5 times.\n"\
                << "program is closing.\n";
            exit(1); // Exits the program with err code 1.
        }
    } while (isMenuPrinted);
    return;
}

void printInstructionMenu() {
    cout << "This chess game is played turn by turn between 2 players.\n"\
        << "The player with the white pieces moves first.\n"\
        << "There are 6 types of pieces, each piece is represented with an abbreviation of their name\n"\
        << "preceded by w or b to differentiate between the black and white pieces."\
        << "The different pieces for 1 player are 8 pawns, 2 rooks(aka castles), 2 knights, 2 bishops, 1 queen, and 1 king.\n\n"\
        <<"";
}

void changeTextColor(HANDLE& consoleColor, int textColorCode) {
    SetConsoleTextAttribute(consoleColor, textColorCode); // Changes the text's color.
}
