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

    void Attack(MovingAnt* Enemy) override;

    void DropPheromones();
    void FollowPheromones();
    void Explore();

protected:
    // Methods

    /*!
     * \brief advance
     * \param phase
     */
    virtual void advance(int phase) override;


    /*!
     * \brief paint Alors ça paint
     * \param painter  c'est beau
     * \param option  ça fait des bulles
     *                 c'est très drole
     * \param widget j'aime
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


    /*!
     * \brief moveAngleTowards
     * \param PointInItemCoordinate
     */
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
