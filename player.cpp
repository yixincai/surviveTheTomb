#include "player.h"

Player::Player(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}

void Player::move(int MaxX, int MaxY){
}

void Player::move(int MaxX, int MaxY, int dir){
	if ((x-20<0&&dir==1) || (x+20>MaxX-30&&dir==2) || (y-20<0&&dir==3) || (y+20>MaxY-30&&dir == 4))
		return;
	if (dir == 1){
    		x -= 20;
    	}
    	else if (dir == 2){
    		x += 20;
    	}
    	else if (dir ==3){
    		y -= 20;
    	}
    	else if (dir == 4){
    		y += 20;
    	}
    
    setPos( x,y );


}

void Player::loseHP(){
}

void Player::changeDir(){
}
