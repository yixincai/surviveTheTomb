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

    gamePlay = new QGraphicsScene();
    gamePlay->setSceneRect(0,0,WindowMaxX,WindowMaxY);
    view = new QGraphicsView( gamePlay );

    mainView_->addWidget(menu_);
    mainView_->addWidget(view);
    
    main = new QGraphicsView(); 
    main->setLayout(mainView_);
    
    timer_monster = new QTimer(this);
    timer_monster->setInterval(500);
    timer_move = new QTimer(this);
    timer_move->setInterval(60);
    timer_gas = new QTimer(this);
    timer_gas->setInterval(1000);
    timer_speed = new QTimer(this);
    timer_speed->setInterval(10000);
}
    timer_monster->start();    timer_move->start();    timer_gas->start();    timer_speed->start();
    

/** Create the board according to the input
  * from the user.
  */
void MainWindow::createBoard(){
  /** Clear the display after pressing start */
  QStandardItemModel* list = new QStandardItemModel();
  solution_->setModel(list);	
  error_->setText("");
  t_list.clear();
  board_->clear();
  /** Check if the user input is empty */
  if(size_->text().isEmpty() || size_->text().isEmpty() || size_->text().isEmpty()){
    error_->setText("Empty input.");
    return;
  }
  bool good =true;
  int size = size_->text().toInt(&good);
  /** Check if the user input is string */
  if (!good){
    error_->setText("Invalid input.");
    return;
  }
  int initMoves = numOfMoves_->text().toInt(&good);
  /** Check if the user input is string again */
  if (!good){
    error_->setText("Invalid input.");
    return;
  }
  int seed = seeds_->text().toInt(&good);
  /** Check if the user input is string and again */
  if (!good){
    error_->setText("Invalid input.");
    return;
  }
  /** Check if board size is invalid */
  if((size != 9 && size != 16) ){
    error_->setText("Invalid input.");
    return;
  }
  b_ = new Board(size,initMoves,seed);
  /** Create tiles, text item in proper position */
	for (int i=0;i<size;i++)
	{
		
		if (size == 9)
		{
			QString str = QString::number(b_->getTiles()[i]);
			
			GUITile *temp = new GUITile((i%(size/3))*50 , (i/(size/3))*50 , 50, 50, this);
			temp->setText(str);
			temp->setNum(b_->getTiles()[i]);
			t_list.push_back(temp);
			board_->addItem(t_list[i] );
			board_->addItem(t_list[i]->getText());
			t_list[i]->getText()->setPos((i%(size/3))*50 , (i/(size/3))*50);
			if (b_->getTiles()[i]==0){
				t_list[i]->setText(""); 
			}
		}
		if (size == 16)
		{
			QString str = QString::number(b_->getTiles()[i]);
			GUITile *temp = new GUITile((i%(size/4))*50 , (i/(size/4))*50 , 50, 50, this);
			temp->setText(str);
			temp->setNum(b_->getTiles()[i]);
			t_list.push_back(temp);
			board_->addItem(t_list[i] );
			board_->addItem(t_list[i]->getText());
			t_list[i]->getText()->setPos((i%(size/4))*50 , (i/(size/4))*50);
			if (b_->getTiles()[i]==0){
				t_list[i]->setText(""); 
			}
		}
	}
	
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
void MainWindow::moveTile(int i){
  /** Do not move the tile is the former move is unfinished */
  if (timer->isActive()){
      	error_->setText("Please wait until the former move to finish.");
    	return;
  }
  /** Do not move the tile is the game is finished */
  if (b_->solved())
  	return;
  try {
    b_->move(i);
  }
  /** Check if the move can be performed */
  catch(std::invalid_argument &er){
    error_->setText("Invalid move.");
    return;
  }
  /** Find source and destination tiles */
  tileToMove=0;
  blank=0;
  for (;tileToMove<t_list.size();tileToMove++){
  	if (t_list[tileToMove]->getNum() == i)
  		break;
  }
  for (;blank<t_list.size();blank++){
  	if (t_list[blank]->getNum() == 0)
  		break;
  }
  timer->start();
  times=0;
  /** Find the direction to go */
  double s_x = t_list[tileToMove]->getX(), s_y = t_list[tileToMove]->getY();
  double d_x = t_list[blank]->getX(), d_y = t_list[blank]->getY();
  if (d_x-s_x>25)
  	dir=4;
  else if (d_x - s_x < -25)
  	dir = 1;
  else if (d_y - s_y> 25)
  	dir = 2;
  else if (d_y - s_y < -25)
  	dir = 3;
  connect(timer,SIGNAL(timeout()),this,SLOT(animation()));
  /** Display solved message */
  solved();
}

/** Perform the animation until the tiles has been 
  * moved 50 timesand stop the timer then
  */
void MainWindow::animation(){
  if (times == 50){
  	timer->stop();
  	return;
  }
  times++;
  /** Move both blank and moving tiles */
  t_list[tileToMove]->move(dir);
  t_list[blank]->move(5-dir);

}


/** Destructor */
MainWindow::~MainWindow()
{
}
