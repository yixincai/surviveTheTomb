#include "zombie.h"

Zombie::Zombie(QPixmap *pm, int x, int y, int vx, int vy) : Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
	hp=5;
}

Zombie::move(int MaxX, int MaxY){
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
    
    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );
}

int Zombie::getHP(){
	return hp;
}

void Zombie::loseHP(){
	hp--;
}
