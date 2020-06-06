#ifndef MOVINGANT_H
#define MOVINGANT_H
#include "ant.h"


class MovingAnt: public Ant
{
public:
    MovingAnt();
    virtual ~MovingAnt();

    void Eat();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    // Methods
    virtual void advance(int phase) override;

    int FoodConsumption;
};

#endif // MOVINGANT_H
