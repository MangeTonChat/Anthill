#ifndef BEEF_H
#define BEEF_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Beef : public QObject, public QGraphicsPixmapItem // inheritance from QObject to use signals
{
    Q_OBJECT

public:
    /*!
     * \brief Beef Constructor
     * \param pixmap , Image to display
     */
    Beef(QPixmap pixmap) : QGraphicsPixmapItem(pixmap){}

    ~Beef() {}

    /*!
     * \brief getEated , Reduce the beef quantity by p_iUnit
     * \param p_iUnit , Quantity to eat
     * \return true if there's is enough left, else false and destroy the object
     */
    bool getEated(const int& p_iUnit)
    {
        m_iBeefQuantity -= p_iUnit;
        if(m_iBeefQuantity  > 0)
            return true;
        else
        {
            this->~Beef();
            return false;
        }
    }

protected:

    int m_iBeefQuantity = 3000; /*!< Current beef quantity left */

};

#endif // BEEF_H

