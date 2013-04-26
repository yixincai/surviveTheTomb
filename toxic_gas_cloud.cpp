#include "toxic_gas_cloud.h"

/** constructor */
ToxicGasCloud::ToxicGasCloud(QPixmap *pm, int x, int y, int vx, int vy) : Thing(pm, x, y, vx, vy ) {
	hp=100;

}
/** move the gas loud with in the scene */
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

/** lose HP which actually does nothing */
void ToxicGasCloud::loseHP(){

}
/** change the direction of the gas */
void ToxicGasCloud::changeDir(){
	velocityX = -velocityX;
	velocityY = -velocityY;
}
