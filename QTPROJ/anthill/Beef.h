#ifndef BEEF_H
#define BEEF_H

#include <QGraphicsPixmapItem>

class Beef : public QGraphicsPixmapItem
{
    public:
    Beef(QPixmap pixmap) : QGraphicsPixmapItem(pixmap){}
};

#endif // BEEF_H

