#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "thing.h"

/**
  This class maintains the location, size, and speed of a Zombie.
  */
class Zombie : public Thing {
public:
    Zombie(QPixmap *pm, int x, int y, int vx, int vy);
    void move(int x, int y);
    int getHP();
    void loseHP();
    void changeDir();
        
};

#endif // ZOMBIE_H
