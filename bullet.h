#ifndef Bullet_H
#define Bullet_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a Bullet.
  */
class Bullet : public Thing {
public:
    Bullet(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    void loseHP();
    void changeDir();
};

#endif // Bullet_H
