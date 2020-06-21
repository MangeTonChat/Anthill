#ifndef QUEEN_H
#define QUEEN_H
#include "movingant.h"
#include "egg.h"
#include "anthill.h"
#include <QElapsedTimer>
#include <QRandomGenerator>


class Queen:public MovingAnt
{
public:
    Queen(Anthill* p_pAnthill);
    virtual ~Queen() {};
    void LayEgg();
    void SignalAnthillUnderAttack();
    void SignalAnthillSafe();
    void GoForNewAnthill();
    void Attack(MovingAnt* Enemy) override;
protected:
    int ResourceConsumptionToLayEggs;
    QElapsedTimer timer;
    virtual void advance(int phase) override;
};

#endif // QUEEN_H
