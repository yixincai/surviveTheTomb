#include "thing.h"

Thing::Thing() {
    pic = NULL;
    x = 0;
    y = 0;
    velocityX = 0;
    velocityY = 0;
}

Thing::Thing(QPixmap *pm, int x, int y, int vx, int vy ) {
    pic = pm;
    setPixmap(*pic);
    x = nx;
    y = ny;
    setPos(x,y);
    velocityX = vx;
    velocityY = vy;
}

int Thing::getVelocityX() {
    return velocityX;
}

int Thing::getVelocityY() {
    return velocityY;
}

void Thing::setVelocityX( int vx ) {
    velocityX = vx;
}

void Thing::setVelocityY( int vy ) {
    velocityY = vy;
}

int Thing::getX() {
    return x;
}

int Thing::getY() {
    return y;
}

void Thing::setX(int nx) {
    x = nx;
}

void Thing::setY(int ny) {
    y = ny;
}

void Thing::setPixmap(QPixmap* pm){
    pic=pm;
}
