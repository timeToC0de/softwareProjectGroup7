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
#include <map> 
#include "Chess.h"

using namespace chessNS; // Allows implementation file to use the chessNS namespace.

using std::string;
using std::cin;
using std::getline;
using std::cout;
using std::endl;
using std::pair;
using std::stoi;

//using namespace std;

using ch = Chess; // Type alias that allows us to use ch instead of Chess. Chess is the class in the namespace chessNS that is in Chess.h.

// I learned the binary search in earlier CSCI classes, I coded it from memory. This only works if the array is ordered.
// Needed because it reduces the search from O(n) for linear search to O(log2n) which is a great improvement.
int binarySearch(char& searchElement, char orderedArr[], const int& arrSize, int& arrPositionOfItem) {

    int lowInd = 0;
    int highInd = arrSize; // Set to the last index of the array.
    int midInd = (highInd + lowInd) / 2;
    bool isFound = false;
    int counter = 0; // May be uesd to count the number of iteration if you would like.

    do {
        if (searchElement < orderedArr[midInd]) { // Search element is less than the current arr value.
            highInd = midInd;
            midInd = (highInd + lowInd) / 2;
        }
        else if (searchElement > orderedArr[midInd]) { // If Search element is greater than the current arr value
            lowInd = midInd;
            midInd = (highInd + lowInd) / 2; // Sets index to the midway point. Floor is used to round down.
        }

        if (searchElement == orderedArr[midInd]) { // Search element is equal to current arr value, therefore it is found.
            isFound = true;
            arrPositionOfItem = midInd; // Sets arrPositionOfItem to the midInd since that is where the search element was.
        }

        counter++;
    } while (!isFound && !(searchElement > orderedArr[arrSize - 1]) && !(searchElement < orderedArr[0])); // Runs until either element is found or the low or high range is surpassed.

    if(!isFound)
        arrPositionOfItem = -1; // If searchElement was not found, then this is set to -1

    return isFound; // Returns true if the search element was found, otherwise returns false.
}

// Deals with draw command.
bool ch::draw() {
    int inputCounter = 0; // Used to prevent an infinite loop if the user fails to enter valid input.
    bool isDrawConfirmed = false;
    char drawChoice; // Used to control whether the instructions are printed.

    do {
        cout << "Enter choice: ";
        cin >> drawChoice; // Allows user to enter y or n to confirm draw or not.
        inputCounter++; // Keeps track of the number of times that the user has input 
        drawChoice = tolower(drawChoice); // Converts to lowercase.
        if (drawChoice == 'y' || drawChoice == 'n') {
            if (drawChoice == 'n') {
                cout << "\nDraw declined.\n";
                cin.ignore(INT_MAX, '\n');
                return false; // returns false since the draw
            }
            else {
                cout << "\nDraw accepted.\n";
                return true;
            }

            isDrawConfirmed = true; // Causes input loop to exit.

        }
        else if (inputCounter > 6) { // If the loop runs 5 times or more.
            cout << "Improper input entered 5 times.\n"\
                << "Program is closing.\n";
            system("pause"); // Pauses so the user can read the message above.
            exit(1); // Exits the program with exit code 1.
        }
        else {
            cout << "Y or N are the only valid options. Please re-enter your decision.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        cout << "\n";

    } while (!isDrawConfirmed); // Runs until the user enters y or n. May exit if the user fails to enter valid input for 5 iterations.

    return false; // Passes control back to calling function. This shouldn't be reached but is here just in case.
}

// If it is white's turn next it returns true, if it's black's turn next it returns false.
bool ch::alternateTurn() {
    // This if-else block controls how the black and white in the top of the board are colored.
    if (isWhitesTurn)
        isWhitesTurn = false; // False means black's perspective of the board will be printed.
    else
        isWhitesTurn = true; // True means white's perspective of the board will be printed.

    return isWhitesTurn; // Returns based on who's turn it was last.
}

// This is the main game loop.
void ch::gameLoop() {

    std::string moveOrCommand; // Used to pass to the move or command functions which will deal with the move or command.
    int turnCount = 0; // Used to count how many turns have occured.
    bool isAMove = false; // Controls whether the move() function is called.
    bool isACommand = false; // Controls whether the command() fuction is called.
    bool isNotValidInput = true; // Controls whether the move must be re-entered.
    bool isGameDone = false; // Ends game when set to true.
    bool isDraw = false; // Used to store true if a draw was offered and accepted.

    //char rowAr[8] = { 'a', 'b', 'c','d','e','f','g','h' };
    int arrSize = 8;
    char* fileArr = new char[arrSize];
    char fileLetter = 'a';

    for (int fileNumber = 0; fileNumber < arrSize; fileNumber++) { // Initializes the char arr that contains the row(aka file) letters.
        fileArr[fileNumber] = fileLetter;
        fileLetter++;
    }

    cin.ignore(INT_MAX, '\n'); // Allows getline in confirmMove() to work properly because it discards the \n that would lead to getline() getting that newline instead of the user's input.
    
    do { // This loops for the duration of the whole game.

        do { // Loop for move/command input validation for each player. One Iteration is one player's turn. The next iteration is the other player's turn.

            isAMove = false;        // If the move was valid then this will cause the input loop to end and it will be the start of the next player's turn.
            isACommand = false;     // If the command was valid then this will cause the input loop to end and it will be the start of the next player's turn.
            isNotValidInput = true; // If this is still true by the end of the loop, then whoever's turn it is will run again because the input was invalid.

            printBoard(boardColor, isWhitesTurn); // Prints board. The isWhitesTurn will control the coloring and words displayed above the board.

            if(isWhitesTurn) // Used to color the prompt for the move so it is different based on who's turn it is.
                SetConsoleTextAttribute(console_color, 15); // Changes the text's color to white.
            else 
                SetConsoleTextAttribute(console_color, 8); // Changes the text's color to grey. 

            moveOrCommand = confirmMove(); // Accepts and formats the user's input.

            if (moveOrCommand.size() > 5) { // The move size should be 5, the command length should be 1.
                cout << "\nInvalid input: " << moveOrCommand << ", make sure you input a valid move or command. e.g pa2 a4 or i\n";
                isNotValidInput = true; // Has the user enter a move or command again. 
            }
            else if (moveOrCommand.size() == 1) { // Command length is 1 so if the user has input longer than that, then it will be treated as a move or an error.
                isACommand = command(moveOrCommand[0], isGameDone, isDraw); // This runs the command that the user input. If the user input q, then the chess game ends and the console shutsdown.
                if (isGameDone) { // This executes only if the user entered q which is the quit game command which ends the game.
                    return;
                }
            }
            else if (moveOrCommand.size() <= 5) { // If the length is 5, then the input is a move, the move() function will validate whether the move was valid.

                isAMove = move(moveOrCommand, fileArr, arrSize); // Deals with the moving of the pieces.
            }
        
            if (isAMove) // If the move is a valid move, then this runs.
                isNotValidInput = false; // Ends turn loop so the other player's turn will execute.
            else if (isACommand) {
                if (isDraw) { // This checks if a draw was accepted during the turn, if it was then the game ends.
                    isGameDone = true; // Ends game loop.
                    isNotValidInput = false; // Ends turn loop.
                }
            }

        } while (isNotValidInput); // If the user didn't input a valid move or the user input a command that shouldn't end the game (q or d), the loop will iterate again.

        alternateTurn(); // Alternates from white's to black's turn or vice versa.
        

    } while (!isGameDone); // Ends when isGameDone is set to true since !true means not true = false, and false ends while loops.

    delete []fileArr; // Prevents memory leaks since fileArr is a dynamic allocated array pointer.
    return;
} // End of gameLoop

// Does the appropriate action based on what command the user entered.
bool ch::command(char& command, bool& isQInput, bool& isDraw) {
    bool isValidCommand = true;

    switch (command) {
        
    case 'd':
        if (isWhitesTurn)
            cout << "\nWhite offered a draw.\nType y if you accept or n to decline then press enter to confirm.\n";
        else
            cout << "\nBlack offered a draw.\nType y if you accept or n to decline then press enter to confirm.\n";
        isDraw = draw();
        break;
    case 'i':
        printInstructionMenu(); 
        break;
    case 'q':
        cout << "\nEnding game.\n";
        isQInput = true;
        break;
    case 'c':
        printListOfCommands();
        break;
    default:
        isValidCommand = false;

        cout << "Invalid Command: " << toupper(command) << "\n";
    }

    return isValidCommand;
}

// Used to move the pieces on the board based on the move entered by the user.
// Refer to the boardSquare.h and .cpp to get the idea of what we are modifying.
// The board is an array of  rows and rows are an array of the boardSquare objects. 
// The boardSquare object is what will change from this function if the move is valid.
// We will have functions here to do the move validation e.g making sure a bishop is moving as a bishop should.
// We must also make sure that no pieces go through any other piece unless they're knights.
// Also, we must make sure that checkmates are checked for etc.
bool ch::move(string& moveInput, char fileNumbers[], const int& fileNumArrSize) {
    bool isValidMove = true; // If the moveInput passes all the validation checks, then this stays true, if it fails one validation, then set it to false to keep the turn from changing.
    int indexForFileN = -1; // Used along with the binary search as a time efficient way of finding whether the file letters entered in the moveInput is valid.
    string thirdChar; // Needed since stoi() must be used. string to int = stoi(). This is the file of the current square.
    string fifthChar; // Used to store the 4th char so that stoi() may be used. This is the file of the destination square.
     
    // These 2 arrays can be used to check if the move is invalid since a piece like a rook can only change rank or file in a turn, not both.
    int fileIndices[2]; // Used to store the file positions that the piece is on and which file the piece will be going to. 
    int rankIndices[2]; // Used to store the rank positions that the piece is on in the first array position and which rank the piece wants to go to.
   
    // Length test.
    switch (moveInput.length()) { // This is the first test. It checks to see if the move input is too small. 5 is valid move input length. Spaces have been removed from the moveInput earlier.

    case 2:
        isValidMove = false;
        break;
    case 3:
        isValidMove = false;
        break;
    case 4:
        isValidMove = false;
        break;
    default:
        // Valid length.
        isValidMove = true; // This signifies that if the switch gets to this then the moveInput passed the first test.
    }

    if (!isValidMove) { // If moveInput had too short of a move input length then the if code block runs.
        cout << "Invalid length for move input: " << moveInput << ", valid move looks like this: pb2 b3\n";
        return isValidMove; // Returns false if the moveInput was too short.
    }

    // First character test.
    switch (moveInput[0]) { // Checks the 1st character of the moveInput.
    case'p':
        break;
    case 'c':
        break;
    case 'n':
        break;
    case 'b':
        break;
    case'q':
        break;
    case 'k':
        break;
    default:
        cout << "Invalid piece: " << moveInput[0] << ", Enter a valid piece name.\n";
        isValidMove = false;
        return isValidMove; // Exits the move() function.
    }
    
    // Second character test.
    // This searches the fileNumbers arr for the file letter that should be in the 2nd spot of the moveInput([1]). If it is not found, then that means the move is not valid.
    isValidMove = binarySearch(moveInput[1], fileNumbers, fileNumArrSize, indexForFileN); 
    if (!isValidMove) {
        cout << "Invalid 2nd character, improper file letter: " << moveInput[3] << ", Re-enter move.\n";
        return isValidMove; // Returns false.
    }
    fileIndices[0] = indexForFileN; // This is the current file that the piece is on. It only gets here if the 2nd char in moveInput was a,b,c,d,e,f,g, or h.

    // Third character test.
    switch (moveInput[2]) {
    case '1':
        break;
    case '2':
        break;
    case '3':
        break;
    case '4':
        break;
    case '5':
        break;
    case '6':
        break;
    case '7':
        break;
    case '8':
        break;
    default:
        cout << "Invalid 3rd character, improper rank number: " << moveInput[2] << ", Re-enter move.\n";
        isValidMove = false;
        return isValidMove; // Returns false.
    }
    thirdChar = moveInput[2]; // Needed so that stoi may be used.
    rankIndices[0] = stoi(thirdChar); // Converts and stores the second character as an int so that it may be used to modify the board.
    
    // Fourth character test.
    // This searches the fileNumbers arr for the file letter that should be in the 4th spot of the moveInput([1]). If it is not found, then that means the move is not valid.
    isValidMove = binarySearch(moveInput[3], fileNumbers, fileNumArrSize, indexForFileN);
    if (!isValidMove) {
        cout << "Invalid 4th character, improper file letter: " << moveInput[3] << ", Re-enter move.\n";
        return isValidMove; // Returns false.
    }
    fileIndices[1] = indexForFileN; // This is the current file that the piece is on. It only gets here if the 2nd char in moveInput was a,b,c,d,e,f,g, or h.

    // Fifth character test.
    switch (moveInput[4]) {
    case '1':
        break;
    case '2':
        break;
    case '3':
        break;
    case '4':
        break;
    case '5':
        break;
    case '6':
        break;
    case '7':
        break;
    case '8':
        break;
    default:
        cout << "Invalid 5th character, improper rank number: " << moveInput[4] << ", Re-enter move.\n";
        isValidMove = false;
        return isValidMove; // Returns false.
    }
    fifthChar = moveInput[4]; // Needed so that stoi may be used.
    rankIndices[1] = stoi(fifthChar); // Converts and stores the second character as an int so that it may be used to modify the board.

    // START OF SECTION that isn't complete: We need to complete these validations/checks.
    // Section for checking whether current and destination are appropriate for the piece entered.

    // Section to check if the piece (contained in moveInput[0]) on the current square corresponds to the current player, an isWhitePiece = false current square is not legal for the white player's turn and vice versa.

    // Check for checks or checkmates here, if it's a check, the user must be told their king is in check.
    // If king is in check and there are no legal moves, then it is a checkmate. Can a piece move in front of the attacking piece.
    // Can the king move out of the way.
    
    // Check if the potential move will put their king in checkmate.
    // If it will, then prevent the move and give message to user prompting for move that doesn't put king in check.
    // END OF VALIDATION SECTION WE NEED TO COMPLETE.

    // Modifies the board, ideally after the input validation occurs.
    cout << "FI[0]:" << fileIndices[0] << ", RI[0]:" << rankIndices[0] << "FI[1]:" << fileIndices[1] << ", RI[1]: " << rankIndices[1] << "\n";
    movePiece(fileIndices[0], rankIndices[0], fileIndices[1], rankIndices[1]); 

    return isValidMove;
}


string ch::confirmMove() {
    string confirmedStringInput = formatInput(getPlayerMove()); // GetPlayerMove() prompts for input, formatInput() removes all the spaces and makes all of the letters lowercase.
    return confirmedStringInput; // Returns the confirmed string input of the move or command the user has input.
}

// Formats string input as needed to make it easier to do input validation.
// The format process is removing all spaces and making all the letters lowercase.
// Making the characters lowercase makes further input processing easier.
// It also truncates the input to be at most 9 characters long since 5 is the valid length for moves and 1 is the valid length for commands.
string ch::formatInput(string strInput) {
    int i;                // Used as a counter.
    char oldStr[30] = {}; // Declares and Initializes a char array with no chars
    char newStr[30] = {}; // Used to store the str after all the spaces have been removed.
    int newStrIndex = 0;  // Declares the var to hold the new str length after the spaces have been removed.
    string newString;

    if (strInput.size() > 30) // If the str passed had a size of 10 or more.
        strInput.resize(29);  // Resizes the strInput to be within bounds of the char array.

    // This for loop I created to load the char array with the characters of the move input by the user.
    for (i = 0; i < strInput.size(); ++i)
    {
        oldStr[i] = strInput[i]; // Fills the char arr with the strInput one place at a time.

        if (oldStr[i] != ' ')    // if the char is not a space then the if block runs.
        {
            if (isupper(oldStr[i]))             // if the char is uppercase.
                oldStr[i] = tolower(oldStr[i]); // Converts uppercase to lowercase.
            newStr[newStrIndex] = oldStr[i];    // Stores the lowercase non-space char into the newStr char arr.
            newStrIndex++;                      // Points to the next spot in the newStr char arr since an element was just added.
        }
    }

    // cout << "Updated input is: " << a << "\n"; // Prints updated string.
    // cout <<"New Str: " << newStr << endl; // Prints old string.
    // cout << "Old Str: " << oldStr << endl; // Prints new string.

    newString = newStr; // Assigns the new string.
    // cout << "String size: " << newString.length() << '\n';
    return newString; // Returns the new string.
}

// Prompts player for input, either a move or command is acceptable. Returns unformatted raw string input from user.
string ch::getPlayerMove() {
    string playerMove; // Stores the move made by the user.

    cout << "  Input move or command: "; // Shortened from "Input move or command and press enter: "; because it did not fit under the board as neatly.

    if (!cin.good()) { // If cin stream is in a bad state, then this will execute the body of the if selection structure.
        cin.ignore(INT_MAX, '\n'); // Clears input stream.
        cin.clear(); // Clears input flags if there are any.
    }
   
    getline(cin, playerMove); // Getline allows for spaces to be accepted in the input.

    // cout << "Player's move: " << playerMove << endl;
    return playerMove;
}


// Use ctrl + k + u on selected lines to uncomment, ctrl + k + c comments the selected lines to easily uncomment these sections. 
// Unused lines of Code:

//void ch::initMap(map<char, int>& rowNumMapArg, pair<char, int>& rowNumArg, map<char, int>::iterator& rnmItr) {
//
//    char rowLetter = 'a';
//
//    for (int rowNumber = 1; rowNumber < 9; rowNumber++) {
//        rowNumArg.first = rowNumber;
//        rowNumArg.second = rowLetter;
//        rowNumMapArg.insert(rowNumArg);
//
//        rowLetter++;
//        rowNumber++;
//    }
//    rnmItr = rowNumMapArg.begin();
//
//    for (rnmItr = rowNumMapArg.begin(); rnmItr != rowNumMapArg.end(); rnmItr++) {
//        cout << rnmItr->first << " " << rnmItr->second << "\n";
//    }
//}


// Use of map to hold the row letter and number relationship of the 
// a:1, b:2, c:3, d:4, e:5, f:6, g:7, h:8.
    //std::map<char, int> rowNumMap;    // Stores all the row numbers corresponding to their letter. Needed for the move input e.g pa2 a4 to transfrom the a to 1 to influence the board data structure.
    //std::pair<char, int> rowNum; // Stores the row letter and the row number.
    //std::map<char, int>::iterator rowNumMapItr; // Iterator for the row num map.
    //for (int rowNumber = 1; rowNumber < 9; rowNumber++) { // Initializes the map.
    //    rowNum.first = rowLetter;
    //    rowNum.second = rowNumber;
    //    rowNumMap.insert(rowNum);

    //    rowLetter++;
    //}

    // Prints the whole map to show the pairings.
    //for (rowNumMapItr = rowNumMap.begin(); rowNumMapItr != rowNumMap.end(); rowNumMapItr++) {cout << "\n" << rowNumMapItr->first << " " << rowNumMapItr->second << "\n";}
