#include "zombie.h"

Zombie::Zombie(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=5;
}

void Zombie::move(int MaxX, int MaxY){
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

    if ( x > MaxX ) {
         velocityX = -velocityX;
         x+=velocityX;
    }

    if ( y > MaxY ) {
         velocityY = -velocityY;
         y+=velocityY;
    }
    
    setPos( x,y );
}

int Zombie::getHP(){
	return hp;
}

void Zombie::loseHP(){
	hp--;
}
