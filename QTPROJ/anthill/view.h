#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>

class View : public QGraphicsView
{
public:

    /*!
   * \brief View Constructor, set the needed parameters
   * \param parent , set the view parents
   */
  explicit View(QWidget *parent = 0) :
    QGraphicsView(parent)
  {

    // Set Background
    //setRenderHint(QPainter::Antialiasing); // Desactivated to improve performance
    setBackgroundBrush(QPixmap(":/images/dirt.png"));

    // Set QGraphicsView Mode
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

  }

protected :

    /*!
   * \brief wheelEvent , Use Ctrl + Wheel to zoom on the scene on the mouse location
   * \param event , the Wheel Event only will activated this function
   */
  void wheelEvent(QWheelEvent *event)
  {
      // Ctrl + Wheel
      if (event->modifiers() & Qt::ControlModifier)
      {
          // zoom
          const ViewportAnchor anchor = transformationAnchor();
          setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
          int angle = event->angleDelta().y();
          qreal factor;
          if (angle > 0) {
              factor = 1.1;
          } else {
              factor = 0.9;
          }
          scale(factor, factor);
          setTransformationAnchor(anchor);
      }
      else {
          QGraphicsView::wheelEvent(event);
      }

  }

  /*!
   * \brief keyPressEvent , Right / Left rotate the scene, just for fun
   * \param event, Right and Left Arrow
   */
  void keyPressEvent(QKeyEvent *event)
  {
    if(event->key() == Qt::Key_Left)
      rotate(1);
    else if(event->key() == Qt::Key_Right)
      rotate(-1);
  }
};

#endif // VIEW_H
