#ifndef ANTHILL_H
#define ANTHILL_H
#include <QGraphicsItem>


class Anthill : public QGraphicsItem
{
public:
    Anthill();
    Anthill(const qreal& p_ray, const QColor& p_anthillColor) : m_rRay(p_ray), colorAnthill(p_anthillColor)  {}
    virtual ~Anthill() {};

    bool consumeFoodStock(int p_Unit);

    QColor const getColor() const {return colorAnthill;}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;
    qreal getRay() const {return m_rRay;}

protected:
    const qreal m_rRay;
    const QColor colorAnthill;
    int IdAnthill;
    int InitialAntNumber;
    int AntNumber;
    int MaxAntNumber;
    const int MaxFoodStock = 30000;
    int AnthillFoodStock = MaxFoodStock;

};

#endif // ANTHILL_H
