#ifndef LARVA_H
#define LARVA_H
#include "staticant.h"
#include <QElapsedTimer>


class Larva: public StaticAnt
{
public:
    Larva(Anthill* p_pAnthill);
    virtual ~Larva() {};

    /*!
     * \brief EvolveToWorker
     */
    void EvolveToWorker();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    static constexpr int TimeLarvaWaitsToEvolve = 10000;    /*!< Time Before Evolution */
    QElapsedTimer timer;                                    /*!< Check time before evolution */

    /*!
     * \brief advance, Manage Evolution
     * \param phase
     */
    virtual void advance(int phase) override;
};

#endif // LARVA_H
