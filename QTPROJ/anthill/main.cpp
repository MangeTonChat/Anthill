#include <QtMath>
#include <QtWidgets>
#include <QRandomGenerator>

#include "ant.h"
#include "queen.h"
#include "warrior.h"
#include "worker.h"
#include "anthill.h"

static constexpr int AnthillCount = 2;
static constexpr int AntCount = 15;



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-700, -700, 1400, 1400);
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
        // Generate random color and coord
        int x = QRandomGenerator::global()->bounded(-500,500);
        int y = QRandomGenerator::global()->bounded(-500,500);
        QColor colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256));
       // x=0;y=0;

        // Create Anthill
        Anthill *anthill= new Anthill(qreal(150),colorAnthill);
        anthill->setPos(x,y);
        scene.addItem(anthill);

        // Create Queen
        Ant *queen = new Queen(anthill);
        queen->setPos(x ,y);
        scene.addItem(queen);

        for (int i = 0; i < AntCount; ++i)
        {
            double angleRandom = QRandomGenerator::global()->bounded(0,628) / 100.0;
            int rayRandom = QRandomGenerator::global()->bounded(0,anthill->getRay());
            //Ant *antWorker = new Worker;
            Ant *antWarrior = new Warrior(anthill);
            antWarrior->setPos(x + rayRandom*std::cos(angleRandom) , y + rayRandom*std::sin(angleRandom));
            scene.addItem(antWarrior);
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
    //timer.start(1000 / 2);

    return app.exec();
}
