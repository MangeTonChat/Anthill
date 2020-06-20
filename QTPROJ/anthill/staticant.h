#ifndef STATICANT_H
#define STATICANT_H
#include "ant.h"


class StaticAnt: public Ant
{
public:
    StaticAnt(Anthill* p_pAnthill);
    ~StaticAnt();
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override=0;
protected:
    virtual void advance(int phase) override=0;
};

#endif // STATICANT_H
