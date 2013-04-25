#include "bullet.h"

/** constructor */
Bullet::Bullet(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}

/** move the bullet */
void Bullet::move(int MaxX, int MaxY){
    MaxX++;
    MaxY++;
    y += velocityY;
    x += velocityX;
    setPos( x,y );
}

/** no lose HP event */
void Bullet::loseHP(){

}
/** no change direction event */
void Bullet::changeDir(){
}
