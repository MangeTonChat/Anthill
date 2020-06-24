#ifndef ANT_H
#define ANT_H

#include <QGraphicsItem>
#include <QGraphicsScene>

#include "anthill.h"


class Ant: public QGraphicsItem
{
public:
    /*!
     * \brief Ant Constructor
     * \param p_pAnthill , Pointer To Home Anthill
     */
    Ant(Anthill* p_pAnthill);

    virtual ~Ant();

    /*!
     * \brief A Cool way to call the desctuctor
     */
    void Die() {this->~Ant();}

    /*!
     * \brief eatToSurvive , Make the ant eat the food stock of its anthill
     * \return true if it can eat, else false
     */
    bool eatToSurvive();

    inline void setIsQueen(bool p_value) {m_bIsAQueen = p_value;}
    inline bool getIsQueen() const {return m_bIsAQueen;}

    /*!
     * \brief takeDamage , Reduce the ant healthpoint by damage
     * \param damage
     */
    void takeDamage(const int damage);

    /*!
     * \brief getAnthill
     * \return Const Pointer To the home anthill
     */
    const Anthill* getAnthill() const {return m_pAnthillOwner;}

    // QGraphics Item Inherited functions

    /*!
     * \brief boundingRect , inherited QGraphicsItem function
     *                      Define the area to repaint the ant
     * \return
     */
    virtual QRectF boundingRect() const override =0;

    /*!
     * \brief shape , inherited QGraphicsItem function
     *                Define the shape for collision
     * \return
     */
    virtual QPainterPath shape() const override =0;

    /*!
     * \brief paint , inherited QGraphicsItem function
     *                Draw the ant each frame
     * \param painter
     * \param option
     * \param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override =0;

protected:
    // Methods

    /*!
     * \brief Call Twice per frame (one with phase = 0 and then phase = 1)
     * \param phase ( 0 or 1 )
     */
    virtual void advance(int phase) override = 0; // QGraphicsItem

    /*!
     * \brief Set The ant colors according to its anthill and class
     * \param p_ColorAnthill => Anrhill color
     * \param p_ColorAntType => Ant color
     */
    virtual void setColors(const QColor& p_ColorAnthill, const QColor& p_ColorAntType) {colorAnthill = p_ColorAnthill; colorAntType = p_ColorAntType;}

    /*!
     * \brief Set the ScaleFactor of the ant
     * \param p_ScaleFactor => 0.3 for average ant
     */
    virtual void setScaleFactor(const qreal& p_ScaleFactor) {ScaleFactor = p_ScaleFactor;}

    // Const
    const qreal MaxSpeed = -3;          /*!< Const , maximum speed */
    const int MaxHealthPoint = 1000;    /*!< Const , Maximum Healthpoint */

    // Member Values

    int m_iHealthPoints = MaxHealthPoint;   /*!< Current healthpoint */
    qreal speed = MaxSpeed;                 /*!< Current speed, pixel to advance per frame */

    Anthill* m_pAnthillOwner;   /*!< Pointer on the Home Anthill. */
    qreal ScaleFactor;          /*!< To store the scaleFactor */
    qreal angle = 0;            /*!< Current angle for small variation */

    QColor colorAnthill;        /*!< Anthill color */
    QColor colorAntType;        /*!< Ant color */

    bool m_bIsAQueen;           /*!< Boolean to know through evolution if it can became a queen */


};

#endif // ANT_H
