#include "toxic_gas_cloud.h"

ToxicGasCloud::ToxicGasCloud(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;

}

void ToxicGasCloud::move(int MaxX, int MaxY){
    y += velocityY;  
    x += velocityX;

    setPos( x,y );
}

