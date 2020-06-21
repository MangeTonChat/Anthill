#ifndef LARVA_H
#define LARVA_H
#include "staticant.h"
#include <QElapsedTimer>


class Larva: public StaticAnt
{
public:
    Larva(Anthill* p_pAnthill);
    virtual ~Larva() {};

    void EvolveToWorker();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    static constexpr int TimeLarvaWaitsToEvolve = 10000;
    int RoundsToWait;
    QElapsedTimer timer;
    virtual void advance(int phase) override;
};

#endif // LARVA_H
