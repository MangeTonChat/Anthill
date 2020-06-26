#ifndef QUEEN_H
#define QUEEN_H
#include "movingant.h"
#include "egg.h"
#include "anthill.h"
#include <QElapsedTimer>
#include <QRandomGenerator>


class Queen:public MovingAnt
{
public:
    Queen(Anthill* p_pAnthill);
    virtual ~Queen() {};

    /*!
     * \brief LayEgg inside the anthill
     */
    void LayEgg();

    /*!
     * \brief Attack another MovingAnt , damage beetween 20 and 25
     * \param Enemy
     */
    void Attack(MovingAnt* Enemy) override;

    /*void SignalAnthillUnderAttack();
    void SignalAnthillSafe();
    void GoForNewAnthill();*/

protected:

    /*!
     * \brief advance, manage egg laying
     * \param phase
     */
    virtual void advance(int phase) override;

    QElapsedTimer timer;

};

#endif // QUEEN_H
