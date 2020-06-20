#ifndef EGG_H
#define EGG_H
#include "staticant.h"
#include <QElapsedTimer>


class Egg: public StaticAnt
{
public:
    Egg(Anthill* p_pAnthill);
    virtual ~Egg() {};
    void EvolveToLarva();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
protected:
    QPixmap PixEgg;
    static constexpr int TimeEggWaitsToEvolve = 8000;
    QElapsedTimer timer;
    virtual void advance(int phase) override;
};

#endif // EGG_H
