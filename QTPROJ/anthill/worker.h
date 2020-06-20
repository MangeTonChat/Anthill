#ifndef WORKER_H
#define WORKER_H
#include "movingant.h"
#include "queen.h"
#include "warrior.h"
#include <QElapsedTimer>
#include <QRandomGenerator>


class Worker:public MovingAnt
{
public:
    Worker(Anthill* p_pAnthill);
    virtual ~Worker() {};

    void EvolveToWarrior();

    void EvolveToQueen();

protected:
    static constexpr int TimeWorkerWaitsToEvolve = 20000;
    QElapsedTimer timer;
    virtual void advance(int phase) override;
};

#endif // WORKER_H
