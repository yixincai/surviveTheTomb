#ifndef GRAVESTONE_H
#define GRAVESTONE_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a Gravestone.
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
