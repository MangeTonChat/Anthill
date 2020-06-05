#ifndef MOVINGANT_H
#define MOVINGANT_H
#include "ant.h"


class MovingAnt: public Ant
{
public:
    MovingAnt();
    virtual ~MovingAnt();

    void Eat();

    virtual QRectF boundingRect() const override = 0;
    virtual QPainterPath shape() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override = 0;

protected:
    // Methods
    virtual void advance(int phase) override = 0;

    int FoodConsumption;
};

#endif // MOVINGANT_H
