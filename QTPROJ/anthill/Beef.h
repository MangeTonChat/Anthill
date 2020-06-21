#ifndef BEEF_H
#define BEEF_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Beef : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Beef(QPixmap pixmap) : QGraphicsPixmapItem(pixmap){}
    ~Beef() {}

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
    int m_iBeefQuantity = 1000;
};

#endif // BEEF_H

