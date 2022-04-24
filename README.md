# softwareProjectGroup7
Group 7's Software project for SDEV265 - System Software Analysis &amp; Project.
Version 0.1

This project is a command line interface version of chess.
It is being developed using C++ and Visual Studio IDE.
We, the developers, are 3 CSCI students and this is a school project.
For this software project, we wrote a requirements analysis document, feasibility study,
risk assessment document, project plan, and design document.
The software development approach we used for the project was expected to be agile but instead 
it has resembled the waterfall approach due to the requirements for the project 
being identifiable early in the development process. 

The chessProject_Group7.cpp is meant to contain the main event-driven game loop.
There are various header files which will contain subclasses of the super class named piece.
Piece will contain the general data structures and functions that are common to all the pieces.
The subclasses will contain specific functions to do move validation of the specific piece.

The main game loop will render a gameboard with the pieces in the standard positions.
The users will have an option to choose what their display name will be and which name 
will correspond to the black or white pieces.
The users will have the option to input commands during each turn to do things like display the
list of commands, have one of their pieces move, undo the move they just made, 
input help to have a guide on moves display on the console window, and various other commands.

Board is a header file to contain a class that will be utilized by the various classes 
that are part of the piece class hierarchy.
The main need is to have a data structure to represent the game board which will allow 
for move validation to be done on each piece. The board will allow for the command line
interface version of a chess board to be rendered. The console window will also update after
every valid move with the new state of the game board being displayed after the move validation.

If a move is invalid, an appropriate message will display and the user must make another move.
The pieces will be represented by abbreviations that are colored using methods from <windows.h>. 
The control of what color the piece will must be controlled by a boolean member 
that is set to true if it is a light piece.

The board class will need functions to do the checking of whether the king
is in check or in checkmate.
Creating the functions to check all the various illegal moves will likely
be the most difficult task.
