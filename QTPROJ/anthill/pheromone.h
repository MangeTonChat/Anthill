#ifndef PHEROMONE_H
#define PHEROMONE_H


class Pheromone
{
public:
    /*!
     * \brief Pheromone => TO DO
     */
    Pheromone();

    ~Pheromone();
    void Reset();
    void Die();
protected:
    int ConsumptionPerRound;
    int Durability;
    int IdAnthill;
    /*QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;*/
};

#endif // PHEROMONE_H
