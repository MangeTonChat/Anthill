#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"


class Warrior:public MovingAnt
{
public:
    Warrior(Anthill* p_pAnthill);
    virtual ~Warrior() {};
    void CollectFood();
    void Attack();
    void DropPheromones();
    void FollowPheromones();
    void Explore();

protected:
    // Methods
    virtual void advance(int phase) override;

    bool isCloseToBorder() const;

    void moveAngleTowards(const QPointF& PointInSceneCoordinate);

    // Member values
    int FoodStock;
    int FoodCapacity;
    int HPTreshold;
};

#endif // WARRIOR_H
