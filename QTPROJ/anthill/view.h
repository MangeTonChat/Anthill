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
  explicit View(QWidget *parent = 0) :
    QGraphicsView(parent)
  {

    // Set Background
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QPixmap(":/images/dirt.png"));

    // Set QGraphicsView Mode
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);


  }

protected :
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

  void keyPressEvent(QKeyEvent *event)
  {
    if(event->key() == Qt::Key_Left)
      rotate(1);
    else if(event->key() == Qt::Key_Right)
      rotate(-1);
  }
};

#endif // VIEW_H
