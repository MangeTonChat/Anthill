#include <QtMath>
#include <QtWidgets>
#include <QRandomGenerator>

#include "ant.h"
#include "queen.h"
#include "warrior.h"
#include "worker.h"
#include "anthill.h"

static constexpr int AnthillCount = 3;
static constexpr int AntCount = 10;



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-500, -500, 1000, 1000);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    /*Anthill *anthill= new Anthill;
    scene.addItem(anthill);


    Ant *queen = new Queen;
    scene.addItem(queen);

    // Init ant object
    for (int i = 0; i < AntCount; ++i)
    {
        Ant *ant = new Warrior;
        ant->setPos(::sin((i * 6.28) / AntCount) * 200,
                      ::cos((i * 6.28) / AntCount) * 200);
        scene.addItem(ant);
    }
    // Init ant object
    for (int i = 0; i < AntCount; ++i)
    {
        Ant *ant = new Worker;
        ant->setPos(::sin((i * 6.28) / AntCount) * 200,
                      ::cos((i * 6.28) / AntCount) * 200);
        scene.addItem(ant);
    }*/

    // Init anthills
    for (int i = 0; i < AnthillCount; ++i)
    {
        Anthill *anthill= new Anthill;
        int x = QRandomGenerator::global()->bounded(-300,300);
        int y = QRandomGenerator::global()->bounded(-300,300);
        anthill->setPos(x,y);
        scene.addItem(anthill);

        qreal ray = anthill->getRay();

        Ant *queen = new Queen;
        queen->setPos(x +ray,y + ray);
        scene.addItem(queen);

        for (int i = 0; i < AntCount; ++i)
        {
            int ax = QRandomGenerator::global()->bounded(anthill->getRay());
            int ay = QRandomGenerator::global()->bounded(anthill->getRay());
            Ant *antWorker = new Worker;
            //Ant *antWarrior = new Warrior;
            antWorker->setPos(x + ax , y + ay);
            scene.addItem(antWorker);
        }
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
    view.showMaximized();

    // Set FPS
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);

    return app.exec();
}
