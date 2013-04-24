#include "toxic_gas_cloud.h"

ToxicGasCloud::ToxicGasCloud(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;

}

void ToxicGasCloud::move(int MaxX, int MaxY){
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

    if ( x+30 > MaxX ) {
         velocityX = -velocityX;
         x+=velocityX;
    }

    if ( y+30 > MaxY ) {
         velocityY = -velocityY;
         y+=velocityY;
    }
    setPos( x,y );
}

