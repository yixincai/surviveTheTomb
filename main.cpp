#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QPushButton>

/**
* @mainpage CSCI 102 Programming Assignment 5

* @section purpose Purpose/Overview
* We are implementing a Qt game.

* @section requirements Requirements
* Class :
* 1. Thing (abstrct class for moving things)
* 2. Mummy, Zombie, Gravestone, ToxicGasCloud, Bullet
* (detailed implementation of different things)
* 3. Player (store the moving properties of a player)
* 4. MainWindow (allow users to start a game with their name and play 
* the game by pressing keys)
* main function :
* Implement gameplay to move player and shoot bullets
* 
* @author Yixin Cai
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
