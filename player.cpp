#include "player.h"

Player::Player(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}

void Player::move(int MaxX, int MaxY){
}

void Player::move(int MaxX, int MaxY, int dir){
	if (x<0 || x+30>MaxX || y<MaxY || y+30>MaxY)
		return;
	if (dir == 1){
    		x -= 4;
    	}
    	else if (dir == 2){
    		y -= 4;
    	}
    	else if (dir ==3){
    		x += 4;
    	}
    	else if (dir == 4){
    		y -= 4;
    	}
    
    setPos( x,y );


}
