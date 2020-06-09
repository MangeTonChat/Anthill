#include <QtMath>
#include <QtWidgets>

#include "ant.h"
#include "warrior.h"
#include "map.h"


static constexpr int AntCount = 100;

//! [0]
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
//! [0]

//! [1]
    QGraphicsScene scene;
    scene.setSceneRect(-500, -500, 1000, 1000);
//! [1] //! [2]
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
//! [2]
    Map Carte(&scene);
    Carte.Generate();
//! [3]
    for (int i = 0; i < AntCount; ++i) {
        Ant *ant = new Warrior;
        ant->setPos(::sin((i * 6.28) / AntCount) * 200,
                      ::cos((i * 6.28) / AntCount) * 200);
        scene.addItem(ant);
    }
//! [3]

//! [4]
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/dirt.png"));
//! [4] //! [5]
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sweaty Anthill"));
    //view.resize(1100, 1100);
    //view.showFullScreen();
    view.showMaximized();
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
