#ifndef WORKER_H
#define WORKER_H
#include "movingant.h"


class Worker:public MovingAnt
{
public:
    Worker(Anthill* p_pAnthill);
    virtual ~Worker() {};
    void EvolveToWarrior();
protected:
    int RoundsToWait;
};

#endif // WORKER_H
