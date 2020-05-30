#ifndef ANTHILL_H
#define ANTHILL_H
//#include <QGraphicsItem>


class Anthill
{
public:
    Anthill();
    ~Anthill();
    /*QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;*/
protected:
    int IdAnthill;
    int InitialAntNumber;
    int AntNumber;
    int MaxAntNumber;
    int InitialFoodStock;
    int AnthillFoodStock;
    int MaxFoodStock;
};

#endif // ANTHILL_H
