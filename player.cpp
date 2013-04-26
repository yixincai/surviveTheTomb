#include "player.h"
/** constructor */
Player::Player(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}
/** move the player which does nothing */
void Player::move(int MaxX, int MaxY){
	MaxX++;
	MaxY++;
}

/** move the player the the given direction */
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
/** does nothing */
void Player::loseHP(){
}
/** does nothing */
void Player::changeDir(){
}
