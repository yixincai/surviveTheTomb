#include "gravestone.h"

Gravestone::Gravestone(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=5;
}

void Gravestone::move(int MaxX, int MaxY){
    y += velocityY;
    x += velocityX;
    setPos( x,y );
}

int Gravestone::getHP(){
	return hp;
}

void Gravestone::loseHP(){
	hp--;
}

void Gravestone::changeDir(){

}
