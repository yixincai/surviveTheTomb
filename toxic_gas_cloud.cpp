#include "toxic_gas_cloud.h"

ToxicGasCloud::ToxicGasCloud(QPixmap *pm, int x, int y, int vx, int vy) : Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
}

ToxicGasCloud::move(int MaxX, int MaxY){
    y += velocityY;  
    x += velocityX;
    
    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );
}

