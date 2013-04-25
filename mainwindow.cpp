#include "mainwindow.h"
#include <cmath>
#include <stdexcept>
#include <QApplication>
#include <QBrush>
#include <iostream>
using namespace std;
/** Default constructor.
 * Organize the Layout of the MainWindow
 * 1. Start and Quit Button
 * 2. Three input boxes
 * 3. Heuristic Selection
 * 4. Board
 * 5. Cheat Button and Solutions
 * 6. Message Box
 *
 * @author Yixin Cai
 */
MainWindow::MainWindow() {

    /** load pictures */
    QPixmap a("gun.jpg"), b("bullet.jpg"), c("mummy_1.jpg"), d("gravestone.jpg"), e("zombie.jpg"), f("toxic_gas_cloud.jpg");
    player_ = new QPixmap(a.scaled(30,30));
    mummy_ = new QPixmap(c.scaled(40,60));
    zombie_ = new QPixmap(e.scaled(40,60));
    toxic_ = new QPixmap(f.scaled(30,30));
    grave_ = new QPixmap(d.scaled(50,50));
    bullet_ = new QPixmap(b.scaled(20,10));
    
    mainView_ = new QGridLayout();
    
    menu_ = new QFormLayout();
    user_ = new QLineEdit();
    start_ = new QPushButton("Start");
    quit_ = new QPushButton("Quit");
    pause_ = new QPushButton("Pause");
    /** make the Start button able to start the program when pressed */
    connect (start_, SIGNAL(clicked()), this, SLOT(startGame()));
    /** make the Quit button able to quit the program when pressed */
    connect (quit_, SIGNAL(clicked()), qApp, SLOT(quit()));
    
    connect (pause_, SIGNAL(clicked()), this, SLOT(pauseGame()));
    name_ = new QLineEdit();
    score_ = new QLineEdit();
    lives_ = new QLineEdit();
    error_ = new QMessageBox();
    
    menu_->addRow("User name: ", user_);
    menu_->addRow(start_);
    menu_->addRow(pause_);
    menu_->addRow(quit_);
    menu_->addRow("Player: ", name_);
    menu_->addRow("Score: ", score_);
    menu_->addRow("Lives: ", lives_);
    menu_->addRow(error_);
    menu_part = new QWidget();
    menu_part->setLayout(menu_);

    gamePlay = new QGraphicsScene();
    gamePlay->setSceneRect(0,0,500,200);
    view = new myView( this );
    view->setScene(gamePlay);
    view->setFocus();     
    mainView_->addWidget(view, 0,0,3,5);    
    mainView_->addWidget(menu_part,0,6);
    main = new QMainWindow();
    c_= new QWidget(main);    
    c_->setLayout(mainView_);
    main->setCentralWidget(c_);
  
    timer_monster = new QTimer(this);
    timer_monster->setInterval(2000);
    connect(timer_monster, SIGNAL(timeout()), this, SLOT(createMonster()));
    timer_move = new QTimer(this);
    timer_move->setInterval(100);
    connect(timer_move, SIGNAL(timeout()), this, SLOT(move()));
    timer_speed = new QTimer(this);
    timer_speed->setInterval(10000);
    connect(timer_speed, SIGNAL(timeout()), this, SLOT(speedUp()));
    p1 = new Player(player_,-100, -100 ,0,0);
    gamePlay->addItem(p1);
}
    

/** Create the board according to the input
  * from the user.
  */
void MainWindow::startGame(){
  /** Clear the display after pressing start */
//  QStandardItemModel* list = new QStandardItemModel();
//  solution_->setModel(list);	
//  error_->setText("");
//  t_list.clear();
//  board_->clear();
  /** Check if the user input is empty */

  if(user_->text().isEmpty() ){
    error_->setText("Please enter user name.");
    return;
  }
  lives = 3;
  score = 0;
  QString str_l = QString::number(lives);
  QString str_s = QString::number(score);
  name_->setText(user_->text());
  score_->setText(str_s);
  lives_->setText(str_l);
  p1 ->setPos(50,50);
  p1 ->setY(50);
  p1 ->setX(50); 
  for (int j=0;j<monsters.size();j++){
  	delete monsters[j];
  }
  monsters.clear();
  for (int k=0;k<bullets_.size();k++){
  	delete bullets_[k];
  }
  bullets_.clear();
  timer_monster->start();
  timer_move->start();       
  timer_speed->start();
	
}

/** display the view */
void MainWindow::show() {
    main->show();
}

/** Move the tile tho certain direction
  * by one pixel at a time until it has been 
  * moved 50 times.
  *
  * @param i direction for the tile to go
  */
void MainWindow::move(){	
	for (int j=0;j<monsters.size();j++){
		monsters[j]->move(500,200);

		if (monsters[j]->collidesWithItem(p1)){
			lives--;
			if (lives == 0){
				timer_monster->stop();
  				timer_move->stop();       
  				timer_speed->stop();
  				error_->setText("You lost the game!");			
			}	
			delete monsters[j];
			monsters.removeAt(j);
		}
	}
	for (int k=0;k<bullets_.size();k++){
		bullets_[k]->move(500,200);
		for (int j=0;j<monsters.size();j++)
			if (monsters[j]->collidesWithItem(bullets_[k])){
				monsters[j]->loseHP();
				score++;
				delete bullets_[k];
				bullets_.removeAt(k);
				if (monsters[j]->getHP()==0){
					delete monsters[j];
					monsters.removeAt(j);
				}
				return;
			}
	}
  QString str_l = QString::number(lives);
  QString str_s = QString::number(score);
  score_->setText(str_s);
  lives_->setText(str_l);
}

void MainWindow::pauseGame(){
  if (lives==0)
  	return;
  if (timer_monster->isActive()){
    timer_monster->stop();
    timer_move->stop();       
    timer_speed->stop();
  }
  else {
    timer_monster->start();
    timer_move->start();       
    timer_speed->start();
  }
}


void MainWindow::speedUp(){
	for (int i=0;i<monsters.size();i++){
		monsters[i]->setVelocityX(2*monsters[i]->getVelocityX());
		monsters[i]->setVelocityY(2*monsters[i]->getVelocityY());
	}
}

void MainWindow::createMonster(){
	int i = rand()%4;
	if (i==0){
		Mummy *m = new Mummy(mummy_, 460, rand()%140, -2, 0);
		gamePlay->addItem(m);
		monsters.push_back(m);
	}
	else if (i==1){
		Zombie *z = new Zombie(zombie_, rand()%460, rand()%140, 4*(rand()%2)-2, 4*(rand()%2)-2);
		gamePlay->addItem(z);
		monsters.push_back(z);
	}
	else if (i==2){
		Gravestone *g = new Gravestone(grave_, rand()%500, rand()%200, -1, 0);
		gamePlay->addItem(g);
		monsters.push_back(g);
	}
	else if (i==3){
		if (monsters.size()==0)
			return;
		int p = rand()%monsters.size();
		ToxicGasCloud *t = new ToxicGasCloud(toxic_, monsters[p]->getX()+60*(rand()%2)-30, monsters[p]->getY()+60*(rand()%2)-30, 6*(rand()%2)-3, 6*(rand()%2)-3);
		gamePlay->addItem(t);
		monsters.push_back(t);
	}
}

void MainWindow::keyPressEvent1(QKeyEvent *e){
	if (!timer_monster->isActive())
		return;
	switch(e->key()){
		case Qt::Key_J:
			p1->move(500,200,1);
			break;
		case Qt::Key_L:
			p1->move(500,200,2);
			break;
		case Qt::Key_I:
			p1->move(500,200,3);
			break;
		case Qt::Key_K:
			p1->move(500,200,4);
			break;
		case Qt::Key_A:
			createBullet(1);
			break;
		case Qt::Key_W:
			createBullet(2);
			break;
		case Qt::Key_S:
			createBullet(3);
			break;
		case Qt::Key_D:
			createBullet(4);
			break;
	};

}

void MainWindow::createBullet(int d){
	if (d==1){
		Bullet *b = new Bullet(bullet_, p1->getX()-30, p1->getY(), -7, 0);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (d == 2){
		Bullet *b = new Bullet(bullet_, p1->getX(), p1->getY()-30, 0, -7);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (d == 3){
		Bullet *b = new Bullet(bullet_, p1->getX(), p1->getY()+30, 0, 7);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (d == 4){
		Bullet *b = new Bullet(bullet_, p1->getX()+30, p1->getY(), 7, 0);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
}


/** Destructor */
MainWindow::~MainWindow()
{
}
