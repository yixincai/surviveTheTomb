#include "mummy.h"

Mummy::Mummy(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=3;
}

void Mummy::move(int MaxX, int MaxY){
    	y += velocityY;
    	x += velocityX;

    if ( x < 0 ) {
        velocityX = -velocityX;
        x +=velocityX;
    }

    if ( y < 0 ) {
        velocityY = -velocityY;
        y +=velocityY;
    }

    if ( x+60 > MaxX ) {
         velocityX = -velocityX;
         x+=velocityX;
    }

    if ( y+80 > MaxY ) {
         velocityY = -velocityY;
         y+=velocityY;
    }
    
    setPos( x,y );
}

int Mummy::getHP(){
	return hp;
}

void Mummy::loseHP(){
	hp--;
}
