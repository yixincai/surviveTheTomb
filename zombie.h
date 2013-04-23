#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a QGraphicsPixmapItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Zombie : public Thing {
public:
    Zombie(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    int getHP();
    void loseHP();
        
};

#endif // ZOMBIE_H
