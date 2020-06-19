#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"
#include "Beef.h"
#include "obstacle.h"


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

    void moveAngleTowards(const QPointF& PointInItemCoordinate);

    // Member values
    int FoodStock;
    int FoodCapacity;
    int HPTreshold;
};

#endif // WARRIOR_H
