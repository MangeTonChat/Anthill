#ifndef QUEEN_H
#define QUEEN_H
#include "movingant.h"


class Queen//:public MovingAnt
{
public:
    Queen();
    ~Queen();
    void LayEgg();
    void SignalAnthillUnderAttack();
    void SignalAnthillSafe();
    void LayNewQueenEgg();
    void GoForNewAnthill();
protected:
    int ResourceConsumptionToLayEggs;
};

#endif // QUEEN_H
