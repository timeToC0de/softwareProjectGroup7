// This implementation file is for the chess.h. 
// Author: Luke P.
// Created: May 8th 2022, Modified: 5/8/2022
// Course: SDEV265
/* Description: This source file contains the definitions for the functions of the Chess header file.
   The main goal is to implement a session of chess which includes formatting the string input by the user 
   so that it is easier to validate and then process. Additionally, the checks for valid moves will likely be done by functions here.*/

#pragma once
#include <string>
#include <iostream>
#include <windows.h> // Used for the functions that control the color of the output.
#include "Chess.h"

using namespace chessNS; // Allows implementation file to use the chessNS namespace.

using std::string;
using std::cin;
using std::getline;
using std::cout;
using std::endl;

using ch = Chess; // Type alias that allows us to use ch instead of Chess. Chess is the class in the namespace chessNS that is in Chess.h.

void ch::move(string& moveCommand) {

}
string ch::confirmMove() {
    string confirmedStringInput = formatInput(getPlayerMove());
    return confirmedStringInput; // Returns the confirmed string input of the move or command the user has input.
}
// Formats string input as needed to make it easier to do input validation.
// The format process is removing all spaces and making all the letters lowercase.
// Making the characters lowercase makes further input processing easier.
string ch::formatInput(string strInput) {
    int i; // Used as a counter.
    char oldStr[30] = {}; // Declares and Initializes a char array with no chars
    char newStr[30] = {}; // Used to store the str after all the spaces have been removed.
    int newStrIndex = 0; // Declares the var to hold the new str length after the spaces have been removed.
    
    if (strInput.size() > 29) // If the str passed had a size of 30 or more.
        strInput.resize(29); // Resizes the strInput to be within bounds of the char array.

    // This for loop I created to load the char array with the characters of the move input by the user.
    for (i = 0; i < strInput.size(); ++i)
    {
        oldStr[i] = strInput[i]; // Fills the char arr with the strInput one place at a time.

        if (oldStr[i] != ' ') // if the char is not a space then the if block runs.
        {
            if (isupper(oldStr[i])) // if the char is uppercase.
                oldStr[i] = tolower(oldStr[i]); // Converts uppercase to lowercase.
            newStr[newStrIndex] = oldStr[i]; // Stores the lowercase non-space char into the newStr char arr.
            newStrIndex++; // Points to the next spot in the newStr char arr since an element was just added.
        }
    }

    // cout << "Updated input is: " << a << "\n"; // Prints updated string.
    cout <<"New Str: " << newStr << endl;
    cout << "Old Str: " << oldStr << endl;
    strInput = newStr; // Assigns the new string.

    return newStr; // Returns the new string.
}

string ch::getPlayerMove() {
    string playerMove; // Stores the move made by the user.

    cout << "\nInput move or command and press enter: ";
    cin.ignore(INT_MAX, '\n');
    cin.clear(); // Clears input flags if there are any.

    getline(cin, playerMove);

    cout << "Player's move: " << playerMove << endl;
    return playerMove;
}