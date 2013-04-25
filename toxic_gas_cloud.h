#ifndef TOXIC_H
#define TOXIC_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a QGraphicsPixmapItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class ToxicGasCloud : public Thing {
public:
    ToxicGasCloud(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    void loseHP();
    void changeDir();
};

#endif // TOXIC_H
