#include <QtMath>
#include <QtWidgets>

#include "ant.h"
#include "warrior.h"

static constexpr int AntCount = 100;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-300, -300, 600, 600);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    // Init ant object
    for (int i = 0; i < AntCount; ++i)
    {
        Ant *ant = new Warrior;
        ant->setPos(::sin((i * 6.28) / AntCount) * 200,
                      ::cos((i * 6.28) / AntCount) * 200);
        scene.addItem(ant);
    }

    // Set View and background
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/images/dirt.png"));

    // Set QGraphicsView Mode
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    // Set Title and init window size
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sweaty Anthill"));
    view.resize(400, 300);
    view.show();

    // Set FPS
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
