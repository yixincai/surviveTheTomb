#include "gravestone.h"

Gravestone::Gravestone(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=7;
}

void Gravestone::move(int MaxX, int MaxY){
	return;
}

int Gravestone::getHP(){
	return hp;
}

void Gravestone::loseHP(){
	hp--;
}
