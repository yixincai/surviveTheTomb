#include "zombie.h"

/** constructor */
Zombie::Zombie(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=3;
}

/** move the zombie within the scene */
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

/** HP of the zombie 
 *@return HP of the zombie
*/

int Zombie::getHP(){
	return hp;
}

/** decrease of HP */
void Zombie::loseHP(){
	hp--;
}
/** change the moving direction of the zombie */
void Zombie::changeDir(){
	velocityX = -velocityX;
	velocityY = -velocityY;
}
