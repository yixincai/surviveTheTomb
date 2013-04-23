#include "mainwindow.h"
#include <cmath>
#include <stdexcept>
#include <QApplication>
#include <QBrush>
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
    setFocus();
    lives = 3;
    score=0;
    
    /** load pictures */
    QPixmap a("gun.jpg"), b("bullet.jpg"), c("mummy_1.jpg"), d("gravestone.jpg"), e("zombie.jpg"), f("toxic_gas_cloud.jpg");
    player_ = new QPixmap(a.scaled(50,50));
    mummy_ = new QPixmap(c.scaled(60,80));
    zombie_ = new QPixmap(e.scaled(60,80));
    toxic_ = new QPixmap(f.scaled(50,50));
    grave_ = new QPixmap(d.scaled(70,70));
    bullet_ = new QPixmap(b.scaled(30,30));
    
    mainView_ = new QHBoxLayout();
    
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
    name_ = new QMessageBox();
    score_ = new QMessageBox();
    lives_ = new QMessageBox();
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
    gamePlay->setSceneRect(0,0,WindowMaxX,WindowMaxY);
    view = new QGraphicsView( gamePlay );

    mainView_->addWidget(menu_part);
    mainView_->addWidget(view);
    
    main = new QGraphicsView(); 
    main->setLayout(mainView_);
    
    timer_monster = new QTimer(this);
    timer_monster->setInterval(5000);
    connect(timer_monster, SIGNAL(timeout()), this, SLOT(createMonster()));
    timer_move = new QTimer(this);
    timer_move->setInterval(5);
    connect(timer_move, SIGNAL(timeout()), this, SLOT(move()));
    timer_gas = new QTimer(this);
    timer_gas->setInterval(1000);
    timer_speed = new QTimer(this);
    timer_speed->setInterval(10000);
    connect(timer_move, SIGNAL(timeout()), this, SLOT(speedUp()));
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
    error_->setText("Empty input.");
    return;
  }
  name_->setText(user_->text());
  score_->setText("0");
  lives_->setText("3");

  p1 = new Player(player_,500,500,0,0);
  gamePlay->addItem(p1);
  timer_monster->start();
  timer_move->start();    
  timer_gas->start();    
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
	for (int i=0;i<monsters.size();i++)
		monsters[i]->move(1000,1000);
	for (int j=0;j<monsters.size();j++){
		if (monsters[j]->collidesWithItem(&p1)){
			lives--;
		}
		for (int k=0;k<bullets_.size();k++)
			if (monsters[j]->collidesWithItem(bullets_[k])){
				monsters[j]->loseHP();
				delete bullets_[k];
				bullets.remove(bullets[k]);
			}
	}
		
}

void MainWindow::pauseGame(){
  timer_monster->stop();
  timer_move->stop();    
  timer_gas->stop();    
  timer_speed->stop();
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
		if (rand()%2){
			Mummy *m = new Mummy(mummy_, rand()%1000, 0, 0, 3);
			gamePlay->addItem(m);
			monsters.push_back(m);
		}
		else{
			Mummy *m = new Mummy(mummy_, 0, rand()%1000, 3, 0);
			gamePlay->addItem(m);
			monsters.push_back(m);
		}
	}
	else if (i==1){
		Zombie *z = new Zombie(zombie_, rand()%1000, rand()%1000, 6*(rand()%2)-3, 6*(rand()%2)-3);
		gamePlay->addItem(z);
		monsters.push_back(z);
	}
	else if (i==2){
		Gravestone *g = new Gravestone(grave_, rand()%1000, rand()%1000, 0, 0);
		gamePlay->addItem(g);
		monsters.push_back(g);
	}
	else if (i==3){
		if (monsters.size()==0)
			return;
		int p = rand()%monsters.size();
		ToxicGasCloud *t = new ToxicGasCloud(toxic_, monsters[p]->getX()+50, monsters[p]->getY()+50, 6*(rand()%2)-3, 6*(rand()%2)-3);
		gamePlay->addItem(t);
		monsters.push_back(t);
	}
}

void MainWindow::keyPressEvent(QKeyEvent *e){
	if (e->key() == Qt::Key_Left){
		p1->move(1000,1000,1);
	}
	else if (e->key() == Qt::Key_Right){
		p1->move(1000,1000,3);
	} 
	else if (e->key() == Qt::Key_Up){
		p1->move(1000,1000,2);
	} 
	else if (e->key() == Qt::Key_Down){
		p1->move(1000,1000,4);
	}
	else if (e->key() == Qt::Key_A){
		Bullet *b = new Bullet(bullet_, p1->getX()-70, p1->getY(), -7, 0);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (e->key() == Qt::Key_W){
		Bullet *b = new Bullet(bullet_, p1->getX(), p1->getY()-70, 0, -7);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (e->key() == Qt::Key_D){
		Bullet *b = new Bullet(bullet_, p1->getX()+70, p1->getY(), 7, 0);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
	else if (e->key() == Qt::Key_S){
		Bullet *b = new Bullet(bullet_, p1->getX(), p1->getY()+70, 0, 7);
		gamePlay->addItem(b);
		bullets_.push_back(b);
	} 
}

/** Destructor */
MainWindow::~MainWindow()
{
}
