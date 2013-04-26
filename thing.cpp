#include "thing.h"

/** default constructor */
Thing::Thing() {
    pic = NULL;
    x = 0;
    y = 0;
    velocityX = 0;
    velocityY = 0;
    hp=0;
}

/** constructor */
Thing::Thing(QPixmap *pm, int nx, int ny, int vx, int vy ) {
    pic = pm;
    QGraphicsPixmapItem::setPixmap(*pic);
    x = nx;
    y = ny;
    setPos(x,y);
    velocityX = vx;
    velocityY = vy;
    hp=0;
}

/** Get the horizontal velocity of the item
* @return velocity in x direction
*/
int Thing::getVelocityX() {
    return velocityX;
}
/** Get the vertical velocity of the item
* @return velocity in y direction
*/
int Thing::getVelocityY() {
    return velocityY;
}
/** Set the horizontal velocity of the item
* @param vx velocity in x direction
*/
void Thing::setVelocityX( int vx ) {
    velocityX = vx;
}
/** Set the horizontal velocity of the item
* @param vy velocity in y direction
*/
void Thing::setVelocityY( int vy ) {
    velocityY = vy;
}
/** Get the horizontal coordinate of the item
* @return x coordinate
*/
int Thing::getX() {
    return x;
}
/** Get the vertical coordinate of the item
* @return y coordinate
*/
int Thing::getY() {
    return y;
}
/** Set the horizontal coordinate of the item
* @param nx coordinate
*/
void Thing::setX(int nx) {
    x = nx;
}
/** Set the vertical coordinate of the item
* @param ny coordinate
*/
void Thing::setY(int ny) {
    y = ny;
}
/** Set the pixmap of the item
* @param pm pixmap of a picture
*/
void Thing::setPixmap(QPixmap* pm){
    pic=pm;
}
/** Get the HP of the item
* @return HP integer
*/
int Thing::getHP(){
	return hp;
}
