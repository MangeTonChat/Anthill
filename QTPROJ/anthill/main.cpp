#include <QtMath>
#include <QtWidgets>
#include <QRandomGenerator>
#include <QDebug>

#include "ant.h"
#include "queen.h"
#include "warrior.h"
#include "map.h"
#include "worker.h"
#include "anthill.h"
#include "view.h"
#include "Beef.h"


static constexpr int AnthillCount = 10;
static constexpr int AnthillRay = 150;
static constexpr int AntCount = 15;
static constexpr double PercentageOfBeef = 0.00 ;
static constexpr int BorderLength = 1000 ;
static constexpr double PercentageOfObstacle = 0.07 ;
static constexpr int PercentageOfWall = 50;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Set Scene
    QGraphicsScene scene;
    scene.setSceneRect(-BorderLength, -BorderLength, 2*BorderLength, 2*BorderLength);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Map Carte(&scene);
    Carte.Generate();

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
        else
        {
            // Create Queen
            Ant *queen = new Queen(anthill);
            queen->setPos(x ,y);
            scene.addItem(queen);

            // Create worker
            for (int i = 0; i < AntCount; ++i)
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

    //Generate some random obstacles
    QPixmap Obstacle = QPixmap(":/images/cobblestone.png");
    SpaceToGenerate = BorderLength - WidthCobble - Obstacle.width()/2;
    for(double i=PercentageOfObstacle*BorderLength; i>0; i--)
    {

        QGraphicsPixmapItem* randomObstacle=new QGraphicsPixmapItem(Obstacle);
        randomObstacle->setScale(0.5);
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomObstacle->setPos(x,y);
        scene.addItem(randomObstacle);
        if(!scene.collidingItems(randomObstacle).isEmpty()) {
            i++;
            delete randomObstacle;
        }
        else{
            //We need to build a wall
            if(QRandomGenerator::global()->bounded(0,100)<=PercentageOfWall)
            {
                int length = QRandomGenerator::global()->bounded(3,5);
                for(int j=0;j<length;j++)
                {
                    QGraphicsPixmapItem* newWall=new QGraphicsPixmapItem(Obstacle);
                    newWall->setScale(0.5);
                    int direction = QRandomGenerator::global()->bounded(0,3);
                    if(direction==0){
                        x=x+WidthCobble;
                        newWall->setPos(x,y);
                    }
                    if(direction==1){
                        y=y-WidthCobble;
                        newWall->setPos(x,y);
                    }
                    if(direction==2){
                        x=x-WidthCobble;
                        newWall->setPos(x,y);
                    }
                    if(direction==3){
                        y=y+WidthCobble;
                        newWall->setPos(x,y);
                    }
                    scene.addItem(newWall);
                    if(!scene.collidingItems(newWall).isEmpty()||qFabs(newWall->pos().x())>SpaceToGenerate||qFabs(newWall->pos().y())>SpaceToGenerate)
                    {
                        i++;
                        delete newWall;
                    }
                }
                i-=length-1;
            }
        }
    }

    //Generate some random bouffe
    QPixmap BeefPixmap = QPixmap(":/images/beef.png");
    SpaceToGenerate = BorderLength - WidthCobble - BeefPixmap.width()/2;
    for(double i=PercentageOfBeef*BorderLength; i>0; i--){
        Beef* randomBeef=new Beef(BeefPixmap);
        randomBeef->setScale(0.5);
        int x = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        int y = QRandomGenerator::global()->bounded(-SpaceToGenerate,SpaceToGenerate);
        randomBeef->setPos(x,y);
        scene.addItem(randomBeef);
        //No collision allowed
        if(!scene.collidingItems(randomBeef).isEmpty()) {
            i++;
            delete randomBeef;
        }
    }

    // Set View and background
    View view;
    view.setScene(&scene);

    // Set Title and init window size
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Sweaty Anthill"));
    view.showMaximized();

    // Set FPS
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);
    //timer.start(1000 / 2);

    return app.exec();
}
