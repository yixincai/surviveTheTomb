#include "bullet.h"

Bullet::Bullet(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;
}

void Bullet::move(int MaxX, int MaxY){
    y += velocityY;
    x += velocityX;
    setPos( x,y );
}

void Bullet::loseHP(){

}

void Bullet::changeDir(){
}
