#ifndef WORKER_H
#define WORKER_H
#include "movingant.h"


class Worker//:public MovingAnt
{
public:
    Worker();
    ~Worker();
    void EvolveToWarrior();
protected:
    int RoundsToWait;
};

#endif // WORKER_H
