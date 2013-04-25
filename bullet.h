#ifndef Bullet_H
#define Bullet_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a Bullet.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Bullet : public Thing {
public:
    Bullet(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    void loseHP();
    void changeDir();
};

#endif // Bullet_H
