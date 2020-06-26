#ifndef WARRIOR_H
#define WARRIOR_H
#include "movingant.h"
#include "Beef.h"
#include "obstacle.h"
#include <QElapsedTimer>


class Warrior:public MovingAnt
{
public:
    /*!
     * \brief Warrior
     * \param p_pAnthill
     */
    Warrior(Anthill* p_pAnthill);

    virtual ~Warrior() {};

    /*!
     * \brief Attack another MovingAnt , damage beetween 5 and 10
     * \param Enemy
     */
    void Attack(MovingAnt* Enemy) override;

    /*void DropPheromones();
    void FollowPheromones();*/

protected:
    // Inherited QGrpahicsItem Functions

    /*!
     * \brief advance, Manage Obstacle , Fight , Food and Go Home trough ant moves
     * \param phase
     */
    virtual void advance(int phase) override;

    bool eatToSurviveWarrior();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Other Methods

    /*!
     * \brief moveAngleTowards , Rotate to face the given point coordinate
     * \param PointInItemCoordinate
     */
    void moveAngleTowards(const QPointF& PointInItemCoordinate);


    // Member values

    bool m_bOnMyWayHome;            /*!< If true, make the ant go to its anthill */
    bool m_bOnMyWayAway;            /*!< If true, make the ant move away for a few seconds and then retry to go Home */
    QElapsedTimer m_Timer;          /*!< Timer to know how much time the ant take to go home, if > 30s , activate OnMyWayAway */

    const int FoodCapacity = 1000;  /*!< Max food that can carry a warrior */
    int FoodStock;                  /*!< Current Warrior Food stock */

};

#endif // WARRIOR_H
