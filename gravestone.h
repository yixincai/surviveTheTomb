#ifndef GRAVESTONE_H
#define GRAVESTONE_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a QGraphicsPixmapItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Gravestone : public Thing {
public:
    Gravestone(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    int getHP();
    void loseHP();
    void changeDir();
};

#endif // GRAVESTONE_H
