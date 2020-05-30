#ifndef MOVINGANT_H
#define MOVINGANT_H
#include "ant.h"


class MovingAnt: public Ant
{
public:
    MovingAnt();
    ~MovingAnt();
    void Move();
    void Eat();
protected:
    int FoodConsumption;
};

#endif // MOVINGANT_H
