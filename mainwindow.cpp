#include "mainwindow.h"
#include <cmath>
#include <stdexcept>
#include <QApplication>
#include <QBrush>
#include <iostream>
#include <fstream>
using namespace std;
/** Default constructor.
 * Organize the Layout of the MainWindow
 * 1. Start, Pause and Quit Button
 * 2. Three input boxes
 * 3. Heuristic Selection
 * 4. Board
 * 5. Cheat Button and Solutions
 * 6. Message Box
 *
 * @author Yixin Cai
 */
MainWindow::MainWindow() {
    ifstream fin;
    fin.open("score.txt");
    string users;
    int scores;
    if (!fin.fail()){
    	fin>>users;
    	fin>>scores;
    	while (!fin.eof()){
    		formerUser.push_back(users);
    		formerScore.push_back(scores);
    		fin>>users;
    		fin>>scores;
    	}
    }
    /** load pictures */
    QPixmap a("gun.png"), b("bullet.png"), c("mummy_1.png"), d("gravestone.png"), e("zombie.png"), f("toxic_gas_cloud.png");
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
    /** pause the game */
    connect (pause_, SIGNAL(clicked()), this, SLOT(pauseGame()));
    name_ = new QLineEdit();
    score_ = new QLineEdit();
    highScore = new QLineEdit();
    lives_ = new QLineEdit();
    error_ = new QMessageBox();
    error_->setText("Enter your name and press start.\nDo not click on OK button.");
    
    menu_->addRow("User name: ", user_);
    menu_->addRow(start_);
    menu_->addRow(pause_);
    menu_->addRow(quit_);
    menu_->addRow("Player: ", name_);
    menu_->addRow("High Score: ", highScore);
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
    mainView_->addWidget(view, 0,0,3,6);    
    mainView_->addWidget(menu_part,0,7,0,1);
    main = new QMainWindow();
    c_= new QWidget(main);    
    c_->setLayout(mainView_);
    main->setCentralWidget(c_);
  
    /** timer to create monsters */
    timer_monster = new QTimer(this);
    timer_monster->setInterval(1000);
    connect(timer_monster, SIGNAL(timeout()), this, SLOT(createMonster()));
    /** timer to move things */
    timer_move = new QTimer(this);
    timer_move->setInterval(100);
    connect(timer_move, SIGNAL(timeout()), this, SLOT(move()));
    /** timer to speed up all things in the scene */
    timer_speed = new QTimer(this);
    timer_speed->setInterval(20000);
    connect(timer_speed, SIGNAL(timeout()), this, SLOT(speedUp()));
    /**create new user and put it outside the view */
    p1 = new Player(player_,-100, -100 ,0,0);
    gamePlay->addItem(p1);
    lives = 0;
    level = 1;
}
    

/** Create the game.  */
void MainWindow::startGame(){
  /** Check if the user input is empty */
  if(user_->text().isEmpty() ){
    error_->setText("Please enter user name.");
    return;
  }
  error_->setText("Click the view.\nPress I, J, K and L to move.\nPress A, S, D and W to shoot.");
  level = 1;
  QBrush whiteBrush(Qt::white);
  view->setBackgroundBrush( whiteBrush );
  lives = 10;
  score = 0;
  QString str_l = QString::number(lives);
  QString str_s = QString::number(score);
  name_->setText(user_->text());
  score_->setText(str_s);
  lives_->setText(str_l);
  p1 ->setPos(50,50);
  p1 ->setY(50);
  p1 ->setX(50); 
  /** clear the former game */
  for (int j=0;j<monsters.size();j++){
  	delete monsters[j];
  }
  monsters.clear();
  for (int k=0;k<gas_.size();k++){
  	delete gas_[k];
  }
  gas_.clear();
  for (int k=0;k<gss_.size();k++){
  	delete gss_[k];
  }
  gss_.clear();
  for (int k=0;k<bullets_.size();k++){
  	delete bullets_[k];
  }
  bullets_.clear();
      	unsigned int i=0;
	for (;i<formerUser.size();i++){
		if (name_->text().toStdString()==formerUser[i]){
			QString str_l = QString::number(formerScore[i]);
			highScore->setText(str_l);
			break;
		}
	}
	if (i==formerUser.size()){
		QString str_l = QString::number(0);
		highScore->setText(str_l);
	}
  /** start the timers */
  timer_monster->start();
  timer_move->start();       
  timer_speed->start();
}

/** display the view */
void MainWindow::show() {
    main->show();
}

/** Move the monsters and bullets.
  */
void MainWindow::move(){
	for (int j=0;j<monsters.size();j++){
		/** move monsters */
		if (monsters[j]->getX()>p1->getX())
			monsters[j]->setVelocityX(-1*abs(monsters[j]->getVelocityX()));
		else
			monsters[j]->setVelocityX(abs(monsters[j]->getVelocityX()));
		if (monsters[j]->getY()>p1->getY())
			monsters[j]->setVelocityY(-1*abs(monsters[j]->getVelocityY()));
		else
			monsters[j]->setVelocityY(abs(monsters[j]->getVelocityY()));
		monsters[j]->move(500,200);
		/** monster hits the player */
		if (monsters[j]->collidesWithItem(p1)){
			lives--;
			if (lives == 0){
				timer_monster->stop();
  				timer_move->stop();       
  				timer_speed->stop();
  				error_->setText("You lost the game!");
  				saveScore();		
			}	
			delete monsters[j];
			monsters.removeAt(j);
		}
	}
	for (int j=0;j<gas_.size();j++){
		/** move gas */
		gas_[j]->move(500,200);
		/** gas hits the player */
		if (gas_[j]->collidesWithItem(p1)){
			lives--;
			if (lives == 0){
				timer_monster->stop();
  				timer_move->stop();       
  				timer_speed->stop();
  				error_->setText("You lost the game!");
  				saveScore();		
			}	
			delete gas_[j];
			gas_.removeAt(j);
		}
	}
	for (int j=0;j<gss_.size();j++){
		/** delete the gravestones outside of the scene */
		if (gss_[j]->getX()<-60||gss_[j]->getY()<-60){
			delete gss_[j];
			gss_.removeAt(j);
			continue;
		}
		/** move graves */
		gss_[j]->move(500,200);
		/** grave hits the player */
		if (gss_[j]->collidesWithItem(p1)){
			lives--;
			if (lives == 0){
				timer_monster->stop();
  				timer_move->stop();       
  				timer_speed->stop();
  				error_->setText("You lost the game!");
  				saveScore();		
			}	
			delete gss_[j];
			gss_.removeAt(j);
		}
	}
	for (int k=0;k<bullets_.size();k++){
		/** remove bullets out of scene */
		if (bullets_[k]->getX()<-20||bullets_[k]->getX()>500||bullets_[k]->getY()<-10||bullets_[k]->getY()>200){
			delete bullets_[k];
			bullets_.removeAt(k);
			continue;
		}
		bullets_[k]->move(500,200);
		/** kill monsters with bullets */
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
				if (score == 50 || score == 200){
					timer_monster->stop();
    					timer_move->stop();       
    					timer_speed->stop();
					newLevel();
				}
				return;
			}
		for (int j=0;j<gss_.size();j++)
			if (gss_[j]->collidesWithItem(bullets_[k])){
				gss_[j]->loseHP();
				score++;
				delete bullets_[k];
				bullets_.removeAt(k);
				if (gss_[j]->getHP()==0){
					delete gss_[j];
					gss_.removeAt(j);
				}
				if (score == 50 || score == 200){
					timer_monster->stop();
    					timer_move->stop();       
    					timer_speed->stop();
					newLevel();
				}
				return;
			}
		for (int j=0;j<gas_.size();j++)
			if (gas_[j]->collidesWithItem(bullets_[k])){
				gas_[j]->loseHP();
				score++;
				delete bullets_[k];
				bullets_.removeAt(k);
				if (score == 50 || score == 200){
					timer_monster->stop();
    					timer_move->stop();       
    					timer_speed->stop();
					newLevel();
				}
				return;
			}
	}
  QString str_l = QString::number(lives);
  QString str_s = QString::number(score);
  score_->setText(str_s);
  lives_->setText(str_l);

}

void MainWindow::newLevel(){
  QString str_l = QString::number(lives);
  QString str_s = QString::number(score);
  score_->setText(str_s);
  lives_->setText(str_l);

  level++;
  if (level == 2){
  	timer_monster->setInterval(500);
  	QBrush blueBrush(Qt::blue);
  	view->setBackgroundBrush( blueBrush );
  }
  else if (level == 3){
  	timer_monster->setInterval(250);
  	QBrush redBrush(Qt::red);
  	view->setBackgroundBrush( redBrush );  
  }
  p1 ->setPos(50,50);
  p1 ->setY(50);
  p1 ->setX(50); 
  /** clear the former game */
  for (int j=0;j<monsters.size();j++){
  	delete monsters[j];
  }
  monsters.clear();
  for (int k=0;k<gas_.size();k++){
  	delete gas_[k];
  }
  gas_.clear();
    for (int k=0;k<gss_.size();k++){
  	delete gss_[k];
  }
  gss_.clear();
  for (int k=0;k<bullets_.size();k++){
  	delete bullets_[k];
  }
  bullets_.clear();
  /** start the timers */
  timer_monster->start();
  timer_move->start();       
  timer_speed->start();

}

/** save scores to a file called score.txt */
void MainWindow::saveScore(){
	QString str_l = QString::number(lives);
  	QString str_s = QString::number(score);
  	score_->setText(str_s);
  	lives_->setText(str_l);
    	ofstream fout;
    	unsigned int i=0;
	for (;i<formerUser.size();i++){
		if (name_->text().toStdString()==formerUser[i]){
			if (score>formerScore[i])
				formerScore[i]=score;
			break;
		}
	}
	if (i==formerUser.size()){
		formerUser.push_back(name_->text().toStdString());
		formerScore.push_back(score);
	}
	fout.open("score.txt");
	for (unsigned int j=0; j<formerUser.size();j++){
		fout<<formerUser[j]<<endl;
		fout<<formerScore[j]<<endl;
	}
}

/** pause the game by stopping the timers */
void MainWindow::pauseGame(){
  if (lives==0)
  	return;
  if (timer_monster->isActive()){
    pause_->setText("Resume");
    timer_monster->stop();
    timer_move->stop();       
    timer_speed->stop();
  }
  else {
    pause_->setText("Pause");
    timer_monster->start();
    timer_move->start();       
    timer_speed->start();
  }
}

/** speed up everything on the screen */
void MainWindow::speedUp(){
	for (int i=0;i<monsters.size();i++){
		monsters[i]->setVelocityX(2*monsters[i]->getVelocityX());
		monsters[i]->setVelocityY(2*monsters[i]->getVelocityY());
	}
	for (int i=0;i<gas_.size();i++){
		gas_[i]->setVelocityX(2*gas_[i]->getVelocityX());
		gas_[i]->setVelocityY(2*gas_[i]->getVelocityY());
	}
	for (int i=0;i<gss_.size();i++){
		gss_[i]->setVelocityX(2*gss_[i]->getVelocityX());
		gss_[i]->setVelocityY(2*gss_[i]->getVelocityY());
	}
}

/** randomly create one of the four monsters */
void MainWindow::createMonster(){
	if (level==1){
		createMonster1();
	}
	else if (level==2){
		createMonster2();
	}
	else if (level==3){
		createMonster3();
	}
}
/** monster frequency for level 1 */
void MainWindow::createMonster1(){
	int i = rand()%2;
	if (i==0){
		Mummy *m = new Mummy(mummy_, 460, rand()%140, -5, 0);
		gamePlay->addItem(m);
		monsters.push_back(m);
	}
	else if (i==1){
		Gravestone *g = new Gravestone(grave_, 300+rand()%150, rand()%150, -3, 0);
		gamePlay->addItem(g);
		gss_.push_back(g);
	}
}

/** monster frequency for level 2 */
void MainWindow::createMonster2(){
	int i = rand()%3;
	if (i==0){
		Mummy *m = new Mummy(mummy_, 460, rand()%140, -8, 6*(rand()%2)-3);
		gamePlay->addItem(m);
		monsters.push_back(m);
	}
	else if (i==1){
		Zombie *z = new Zombie(zombie_, 200+rand()%260, rand()%140, 10*(rand()%2)-5, 10*(rand()%2)-5);
		gamePlay->addItem(z);
		monsters.push_back(z);
	}
	else if (i==2){
		Gravestone *g = new Gravestone(grave_, 200+rand()%250, rand()%150, -5, 0);
		gamePlay->addItem(g);
		gss_.push_back(g);
	}
}
/** monster frequency for level 3 */
void MainWindow::createMonster3(){
	int i = rand()%4;
	if (i==0){
		Mummy *m = new Mummy(mummy_, 460, rand()%140, -14, 10*(rand()%2)-5);
		gamePlay->addItem(m);
		monsters.push_back(m);
	}
	else if (i==1){
		Zombie *z = new Zombie(zombie_, 200+rand()%260, rand()%140, 14*(rand()%2)-7, 14*(rand()%2)-7);
		gamePlay->addItem(z);
		monsters.push_back(z);
	}
	else if (i==2){
		Gravestone *g = new Gravestone(grave_, 200+rand()%250, rand()%150, -10, 0);
		gamePlay->addItem(g);
		gss_.push_back(g);
	}
	else if (i==3){
		if (monsters.size()==0)
			return;
		int p = rand()%monsters.size();
		ToxicGasCloud *t = new ToxicGasCloud(toxic_, monsters[p]->getX(), monsters[p]->getY(), 18*(rand()%2)-9, 18*(rand()%2)-9);
		gamePlay->addItem(t);
		gas_.push_back(t);
	}
}
/** captuer key presses and move user or shoot bullet */
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

/** create bullet 
  * @param d the direction of bullets
  */
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
