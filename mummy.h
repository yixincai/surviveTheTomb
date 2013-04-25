#ifndef MUMMY_H
#define MUMMY_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a Mummy.
  */
class Mummy : public Thing {
public:
    Mummy(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    int getHP();
    void loseHP();
    void changeDir();

};

#endif // MUMMY_H
