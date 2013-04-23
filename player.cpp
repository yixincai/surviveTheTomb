#include "player.h"

Player::Player(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}

void Player::move(int MaxX, int MaxY){
}

void Player::move(int MaxX, int MaxY, int dir){
	if (dir == 1){
    		x -= 5;
    	}
    	else if (dir == 2){
    		y -= 5;
    	}
    	else if (dir ==3){
    		x += 5;
    	}
    	else if (dir == 4){
    		y -= 5;
    	}
    
    setPos( x,y );


}
