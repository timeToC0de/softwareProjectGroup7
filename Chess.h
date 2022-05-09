// Contains the namespace holding the Chess class. The class only holds the declarations and not the definitions for the class functions.
// Go to Chess.cpp implementation file to see the function definitions.
#pragma once
#include "board.h"

#ifndef H_Chess
#define H_Chess

namespace chessNS { // NS stands for namespace. Used to remove the worry about having naming conflicts around the definitions of these class functions.

class Chess : protected board { // Chess is a subclass of the superclass, board. Chess is the class to contain functions to run a game of chess.
public:
    Chess() : board() {
        std::string moveOrCommand;
        moveOrCommand = confirmMove();
        std::cout << moveOrCommand;

        if (isWhitesTurn)
            isWhitesTurn = false; // False means black's perspective of the board will be printed.
        else
            isWhitesTurn = true; // True means white's perspective of the board will be printed.
        
        std::cout << "\n\n";
        printBoard(boardColor, isWhitesTurn); // Prints board
        // cout << board::chessBoard[1].rank[1].toChar();
    }

protected:
    std::string confirmMove();
    std::string getPlayerMove();
    std::string formatInput(std::string strInput);
    void move(std::string& moveCommand);

};// End of Chess class declarations.
} // End of chessNS namespace.
#endif //!H_Chess