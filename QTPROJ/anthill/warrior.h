#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"


class Warrior:public MovingAnt
{
public:
    Warrior();
    virtual ~Warrior() {};
    void CollectFood();
    void Attack();
    void DropPheromones();
    void FollowPheromones();
    void Explore();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    // Methods
    virtual void advance(int phase) override;

    int FoodStock;
    int FoodCapacity;
    int HPTreshold;
};

#endif // WARRIOR_H
