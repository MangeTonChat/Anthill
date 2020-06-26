#include <QtMath>
#include <QtWidgets>
#include <QRandomGenerator>
#include <QDebug>

#include "ant.h"
#include "egg.h"
#include "queen.h"
#include "warrior.h"
#include "map.h"
#include "worker.h"
#include "anthill.h"
#include "view.h"
#include "Beef.h"
#include "obstacle.h"

static constexpr int    AnthillCount            = 3;
static constexpr int    AnthillRay              = 100;
static constexpr int    AntCount                = 1;
static constexpr int    BorderLength            = 1500 ; // Scene size , it's a square
static constexpr double PercentageOfBeef        = 7 ; //  %

// Obstacle
static constexpr double PercentageOfObstacle    = 40 ; // %
static constexpr int    PercentageOfWall        = 90; // percent of continuous walls
static constexpr int    WallMinLength           = 3;
static constexpr int    WallMaxLength           = 5;



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-BorderLength, -BorderLength, 2*BorderLength, 2*BorderLength);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Map Carte(&scene);
    Carte.Generate(BorderLength,PercentageOfObstacle,PercentageOfWall,WallMaxLength, WallMinLength, PercentageOfBeef);

    // needed
    int WidthCobble = (QPixmap(":/images/cobblestone.png").width()/2);

    // Avoid Anthill creation in the border
    int SpaceToGenerate = BorderLength - WidthCobble + 3 - AnthillRay;

    // Init anthills
    for (int i = 0; i < AnthillCount; ++i)
    {
        // Generate random color and coord
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        QColor colorAnthill = QColor(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256));

        // Create Anthill
        Anthill *anthill= new Anthill(qreal(AnthillRay),colorAnthill);
        anthill->setPos(x,y);
        scene.addItem(anthill);

        // avoid anthill superposition
        if(!scene.collidingItems(anthill).isEmpty())
        {
            i--;
            delete anthill;
        }
        // If the space is free, create the anthill
        else
        {
            // Create Queen
            Ant *queen = new Queen(anthill);
            queen->setPos(x ,y);
            scene.addItem(queen);

            // Create worker
            for (int i = 0; i < AntCount; ++i) // antCount
            {
                // Generate ant in the anthill
                double angleRandom = QRandomGenerator::global()->bounded(0,628) / 100.0;
                int rayRandom = QRandomGenerator::global()->bounded(0,anthill->getRay());
                Ant *antWorker = new Worker(anthill);
                antWorker->setPos(x + rayRandom*std::cos(angleRandom) , y + rayRandom*std::sin(angleRandom));
                scene.addItem(antWorker);
            }

            // Create Warrior
            for (int i = 0; i < AntCount; ++i)
            {
                // Generate ant in the anthill
                double angleRandom = QRandomGenerator::global()->bounded(0,628) / 100.0;
                int rayRandom = QRandomGenerator::global()->bounded(0,anthill->getRay());
                Ant *antWarrior = new Warrior(anthill);
                antWarrior->setPos(x + rayRandom*std::cos(angleRandom) , y + rayRandom*std::sin(angleRandom));
                scene.addItem(antWarrior);
            }
        }
    }

    // Set View and background
    View* view = new View();
    view->setScene(&scene);

    // Open GL to warm up the GPU
    QOpenGLWidget *gl = new QOpenGLWidget();
    // Antialiasing
    /*QSurfaceFormat format;
    format.setSamples(4);
    gl->setFormat(format);*/
    view->setViewport(gl);

    // Set Title and init window size
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sweaty Anthill"));
    view->showMaximized();

    // Set FPS
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);
    //timer.start(1000 / 10);

    return app.exec();
}
