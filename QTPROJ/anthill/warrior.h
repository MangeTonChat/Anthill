#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"


class Warrior:public MovingAnt
{
public:
    Warrior();
    ~Warrior();
    void CollectFood();
    void Attack();
    void DropPheromones();
    void FollowPheromones();
    void Explore();
protected:
    int FoodStock;
    int FoodCapacity;
    int HPTreshold;
};

#endif // WARRIOR_H
