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
#include "myview.h"

#define WindowMaxX 1000
#define WindowMaxY 1000

using namespace std;
/**
 * A class to display and allow the user to play the game.

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
    /** A timer for to create monsters */
    QTimer* timer_monster;
    /** A timer for things to move */
    QTimer* timer_move;
    /** A timer to speed up */
    QTimer* timer_speed;
    
    /** A widget to contain everything */
    QWidget *menu_part;
    /** A form layout to contain the menu */
    QFormLayout *menu_;
    
    /** A box to allow the user to enter his name */
    QLineEdit *user_;
    /** A PushButton to start the game */
    QPushButton *start_;
    /** A PushButton to quit the game */
    QPushButton *quit_;
    /** A PushButton to pause the game */
    QPushButton *pause_;
    
    /** A box to show the user name */
    QLineEdit* name_;
    /** A box to show the high score */
    QLineEdit* highScore;
    /** A box to show the score */ 
    QLineEdit* score_;
    /** A box to show the remaining lives */
    QLineEdit* lives_;
    /** A LineEdit to show error message or the game stage */
    QMessageBox *error_;
     
    /** A scene to game display */
    QGraphicsScene *gamePlay;
    /** A view to show the scene and capture the key press event */
    myView *view;
    /** A widget to contain the whole view */ 
    QWidget *c_;
    /** A layout to organize the view */
    QGridLayout *mainView_;
    /** A pointer to everything to display */
    QMainWindow *main;

    /** A list of all the monsters */
    QList<Thing*> monsters;
    /** A list of all the gases */
    QList<ToxicGasCloud*> gas_;
    /** A list of all the gravestones */
    QList<Gravestone*> gss_;
    /** A list of all bullets */
    QList<Bullet*> bullets_;
    /** The player */
    Player* p1;
    /** Pixmaps for everything */
    QPixmap* mummy_;
    QPixmap* zombie_;
    QPixmap* toxic_;
    QPixmap* grave_;
    QPixmap* bullet_;
    QPixmap* player_;
    /** Lives the user has */
    int lives;
    /** score of the user */
    int score;
    /** level the user is in */
    int level;
    /** A list of user names who played the game before */
    vector<string> formerUser;
    /** A list of former high scores */
    vector<int> formerScore;

public slots:
    /** Clear the scene and create a new game */
    void startGame();
    /** Pause the game */
    void pauseGame();
    /** Create the bullets */
    void createBullet(int d);
    /** Create the monsters for level 1 */
    void createMonster1();
    /** Create the monsters for level 2 */
    void createMonster2();
    /** Create the monsters for level 3 */
    void createMonster3();
    /** Create the monsters */
    void createMonster();
    /** speed up everything in the scene */
    void speedUp();
    /** move everything */
    void move();
    /** save scores to a file called score.txt */
    void saveScore();
    /** clear the screen for new level */
    void newLevel();
public:
    /** Capture the movement of the key from the view */
    void keyPressEvent1(QKeyEvent *e);
};

#endif 
