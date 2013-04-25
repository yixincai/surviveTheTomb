#ifndef PLAYER_H
#define PLAYER_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a QGraphicsPixmapItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
  */
class Player : public Thing {
public:
    Player(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    void loseHP();
    void changeDir();
    
public slots:
    void move(int x, int y, int dir);
};

#endif // PLAYER_H
