#ifndef ANTHILL_H
#define ANTHILL_H
#include <QGraphicsItem>


class Anthill : public QGraphicsItem
{
public:
    Anthill();

    /*!
     * \brief Anthill Constructor
     * \param p_ray , Ray of the anthill circle
     * \param p_anthillColor , Color for the anthill Ant
     */
    Anthill(const qreal& p_ray, const QColor& p_anthillColor) : m_rRay(p_ray), colorAnthill(p_anthillColor)  {}

    virtual ~Anthill() {};

    /*!
     * \brief consumeFoodStock , Try to consume the food stock of the anthill
     * \param p_Unit , Unit consumed
     * \return true if there's enough food, else false
     */
    bool consumeFoodStock(int p_Unit);

    /*!
     * \brief bringMeFood , fill The foodstock by p_Unit
     * \param p_Unit
     */
    void bringMeFood(int p_Unit);

    /*!
     * \brief canLayEgg , Return true if the foodstock is enough filled to layEgg
     * \return
     */
    bool canLayEgg();

    /*!
     * \brief EggLayed , Reduce FoodStock for each egg layed
     */
    void EggLayed();

    inline QColor const getColor() const {return colorAnthill;}

    inline qreal getRay() const {return m_rRay;}

    inline int getMaxFoodStock() const { return MaxFoodStock;}


    // Inherited QGraphics Item Functions

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void advance(int phase) override;


protected:

    const qreal m_rRay;                         /*!< Ray of the anthill circle limitation */
    const QColor colorAnthill;                  /*!< Ant colors linked to this anthill */

    const int MaxFoodStock = 10000;             /*!< Maximum food unit that can store the anthill */
    int AnthillFoodStock = MaxFoodStock;        /*!< Current food stock */

    /*int IdAnthill;
    int InitialAntNumber;
    int AntNumber;
    int MaxAntNumber;*/

};

#endif // ANTHILL_H
