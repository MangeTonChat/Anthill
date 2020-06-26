#ifndef WORKER_H
#define WORKER_H
#include "movingant.h"
#include "queen.h"
#include "warrior.h"
#include <QElapsedTimer>
#include <QRandomGenerator>


class Worker:public MovingAnt
{
public:

    /*!
     * \brief Worker Constructor
     * \param p_pAnthill
     */
    Worker(Anthill* p_pAnthill);

    virtual ~Worker() {};

    /*!
     * \brief EvolveToWarrior
     */
    void EvolveToWarrior();

    /*!
     * \brief EvolveToQueen
     */
    void EvolveToQueen();

    /*!
     * \brief Attack another MovingAnt , damage beetween 1 and 5
     * \param Enemy
     */
    void Attack(MovingAnt* Enemy) override;

protected:


    static constexpr int TimeWorkerWaitsToEvolve = 12000;   /*!< Time Before Evolution */
    QElapsedTimer timer;                                    /*!< Check time before evolution */

    /*!
     * \brief advance, Manage Evolution
     * \param phase
     */
    virtual void advance(int phase) override;
};

#endif // WORKER_H
