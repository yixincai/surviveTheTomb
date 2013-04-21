#include "mummy.h"

Mummy::Mummy(QPixmap *pm, int x, int y, int vx, int vy, bool v_d) : Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
	vertical_direc = v_d;
	hp=3;
}

Mummy::move(int MaxX, int MaxY){
    if (vertical_direc)	
    	y += velocityY;
    else    
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

int Mummy::getHP(){
	return hp;
}

void Mummy::loseHP(){
	hp--;
}
