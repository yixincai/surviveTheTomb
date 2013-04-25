#include "gravestone.h"

/** constructor */
Gravestone::Gravestone(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=5;
}

/** move the gravestone */
void Gravestone::move(int MaxX, int MaxY){
    MaxX++;
    MaxY++;
    y += velocityY;
    x += velocityX;
    setPos( x,y );
}

/** get the HP of the gravestone
  * @return hp
  */
int Gravestone::getHP(){
	return hp;
}

/** reduce the HP of the gravestone */
void Gravestone::loseHP(){
	hp--;
}

/** no change direction event */
void Gravestone::changeDir(){

}
