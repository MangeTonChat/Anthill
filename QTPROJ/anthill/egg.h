#ifndef EGG_H
#define EGG_H
#include "staticant.h"
#include <QElapsedTimer>


class Egg: public StaticAnt
{
public:
    Egg(Anthill* p_pAnthill);
    virtual ~Egg() {};

    /*!
     * \brief EvolveToLarva
     */
    void EvolveToLarva();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    QPixmap PixEgg;                                     /*!< Egg Image */

    static constexpr int TimeEggWaitsToEvolve = 8000;   /*!< Time Before Evolution */
    QElapsedTimer timer;                                /*!< Check time before evolution */

    /*!
     * \brief advance , Manage Evolution
     * \param phase
     */
    virtual void advance(int phase) override;
};

#endif // EGG_H
