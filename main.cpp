#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QPushButton>

/**
* @mainpage CSCI 102 Programming Assignment 5

* @section purpose Purpose/Overview
* We are implementing a Qt gameplay to display a board which
* allows player to play and cheat.

* @section requirements Requirements
* Class :
* 1. Board (store a board and generate potential moves)
* 2. PuzzleHeuristic, OutOfPlaceHeuristic, ManhattanHeuristic
* (calculate scores for a board compared to solved board)
* 3. PuzzleMove (store a board, tileMove, numberOfMoves, Heuristic
* scores and pointer to previous board)
* 4. PMMinList (a list to store PuzzleMove)
* 5. PuzzleSolver (return solutions (a series of moves) to a given 
* board)
* 6. GUITile (a tile to move and display each tile)
* 7. MainWindoe (allow users to start a game with their input, play 
* the game by pressing each tile and cheat)
* main function :
* Implement gameplay to move tiles through animation and show cheats
* 
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

 
    w.show();

    return a.exec();
}
