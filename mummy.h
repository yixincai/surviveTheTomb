#ifndef MUMMY_H
#define MUMMY_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a QGraphicsPixmapItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Mummy : public Thing {
public:
    Mummy(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    int getHP();
    void loseHP();

};

#endif // MUMMY_H
