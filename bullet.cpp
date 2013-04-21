#include "bullet.h"

Bullet::Bullet(QPixmap *pm, int x, int y, int vx, int vy) : Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
}

Bullet::move(int MaxX, int MaxY){
    y += velocityY;
    x += velocityX;
    QPointF p( x, y );
    QRectF r( rect() );
    r.moveTo(p);
    setRect( r );
}

