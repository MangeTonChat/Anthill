#ifndef ANTHILL_H
#define ANTHILL_H
#include <QGraphicsItem>


class Anthill : public QGraphicsItem
{
public:
    Anthill();
    virtual ~Anthill() {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;
    qreal getRay() const {return m_rRay;}
protected:
    const qreal m_rRay = 200;
    int IdAnthill;
    int InitialAntNumber;
    int AntNumber;
    int MaxAntNumber;
    int InitialFoodStock;
    int AnthillFoodStock;
    int MaxFoodStock;
};

#endif // ANTHILL_H
