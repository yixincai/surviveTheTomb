#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <cstring>
#include <QKeyEvent>
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
#include <QGridLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QMessageBox>
#include <QString>
#include "thing.h"
#include "mummy.h"
#include "zombie.h"
#include "toxic_gas_cloud.h"
#include "gravestone.h"
#include "bullet.h"
#include "player.h"

#define WindowMaxX 1000
#define WindowMaxY 1000

/**
 * A class to display and allow the user to play the puzzle game.

 * @author Yixin Cai
 */
class MainWindow : public QMainWindow  {
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
    QTimer* timer_monster;
    QTimer* timer_move;
    QTimer* timer_speed;
    
    /** A vertical layout to organize view */
    QWidget *menu_part;
    QFormLayout *menu_;
    
    QLineEdit *user_;
    /** A PushButton to start the game */
    QPushButton *start_;
    /** A PushButton to quit the game */
    QPushButton *quit_;
    
    QPushButton *pause_;
    
    QLineEdit* name_;
    QLineEdit* score_;
    QLineEdit* lives_;
    /** A LineEdit to show error message or the game stage */
    QMessageBox *error_;
     
    /** A pointer to game display */
    QGraphicsScene *gamePlay;
    /** A pointer to view of the game */
    QGraphicsView *view;    
    
    /** A layout to organize the whole view */
    QGridLayout *mainView_;
    /** A pointer to everything to display */
    QGraphicsView *main;

    /** A list of all the tiles */
    QList<Thing*> monsters;
    QList<Bullet*> bullets_;
    Player* p1;
    QPixmap* mummy_;
    QPixmap* zombie_;
    QPixmap* toxic_;
    QPixmap* grave_;
    QPixmap* bullet_;
    QPixmap* player_;
    /** How many times the tiles has moved */
    int lives;
    int score;

public slots:
    /** Clear the scene and create a new board */
    void startGame();
    void pauseGame();
    /** Tell if the puzzle is solved */
    void createBullet(int d);
    void createMonster();
    void speedUp();
    void move();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif 
