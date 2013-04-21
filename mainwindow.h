#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <cstring>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QMessageBox>
#include "thing.h"
#include "mummy.h"
#include "zombie.h"
#include "toxic_gas_cloud.h"
#include "gravestone.h"
#include "bullet.h"

#define WindowMaxX 1000
#define WindowMaxY 1000

/**
 * A class to display and allow the user to play the puzzle game.

 * @author Yixin Cai
 */
class MainWindow : public QGraphicsView  {
    Q_OBJECT
    
public:
    /**  default constructor */
    explicit MainWindow();
    /**  destructor */
    ~MainWindow();
    /**  display the window */
    void show();
    
private:
    /** A pointer to timer for animation */
    QTimer* timer_monster, timer_move, timer_gas, timer_speed;
    
    /** A vertical layout to organize view */
    QFormLayout *menu_;
    
    QLineEdit *user_;
    /** A PushButton to start the game */
    QPushButton *start_;
    /** A PushButton to quit the game */
    QPushButton *quit_;
    
    QPushButton *pause_;
    
    QMessageBox* name_, score_, lives_;
    /** A LineEdit to show error message or the game stage */
    QMessageBox *error_;   
     
    /** A pointer to game display */
    QGraphicsScene *gamePlay;
    /** A pointer to view of the game */
    QGraphicsView *view;    
    
    /** A layout to organize the whole view */
    QHBoxLayout *mainView_;
    /** A pointer to everything to display */
    QGraphicsView *main;

    /** A list of all the tiles */
    QList<Thing*> myThings;
    /** How many times the tiles has moved */
    int lives, score;
    /** The direction the tile is going to move */
    string name;

public slots:
    /** Clear the scene and create a new board */
    void startGame();
    void pauseGame();
    /** Tell if the puzzle is solved */
    void solved();
    /** Animation to move the tile */
    void animation();
};

#endif 
