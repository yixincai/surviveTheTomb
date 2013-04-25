#include "mummy.h"

/** constructor */
Mummy::Mummy(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=1;
}
/** move the mummy within the scene 
 ** @param MaxX width of the view
 ** @param MaxY height of the view
*/
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

    if ( x+40 > MaxX ) {
         velocityX = -velocityX;
         x+=velocityX;
    }

    if ( y+60 > MaxY ) {
         velocityY = -velocityY;
         y+=velocityY;
    }
    
    setPos( x,y );
}

/** get the HP
  * @return HP
  */
int Mummy::getHP(){
	return hp;
}

/** decrease the HP */
void Mummy::loseHP(){
	hp--;
}

/** no change direction event */
void Mummy::changeDir(){

}
