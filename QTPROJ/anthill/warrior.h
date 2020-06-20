#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"
#include "Beef.h"
#include "obstacle.h"
#include <QElapsedTimer>


class Warrior:public MovingAnt
{
public:
    Warrior(Anthill* p_pAnthill);
    virtual ~Warrior() {};
    void CollectFood();

    void Attack(Warrior* Enemy, int damage);

    void DropPheromones();
    void FollowPheromones();
    void Explore();

protected:
    // Methods
    virtual void advance(int phase) override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void moveAngleTowards(const QPointF& PointInItemCoordinate);

    // Member values
    bool m_bOnMyWayHome;
    bool m_bOnMyWayAway;
    int FoodStock;
    const int FoodCapacity = 1000;
    int HPThreshold;
    QElapsedTimer m_Timer;

};

#endif // WARRIOR_H
