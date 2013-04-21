#include "gravestone.h"

Gravestone::Gravestone(QPixmap *pm, int x, int y, int vx, int vy) : Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
	vertical_direc = v_d;
	hp=7;
}

Gravestone::move(int MaxX, int MaxY){
}

int Gravestone::getHP(){
	return hp;
}

void Gravestone::loseHP(){
	hp--;
}
