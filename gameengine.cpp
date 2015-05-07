#include "gameengine.h"

#include <QPropertyAnimation>
#include <QAction>

GameEngine *GameEngine::m_instance = 0;
int GameEngine::currentLevelIndex = 0;
int GameEngine::numOfLevels = 0;
QTimer GameEngine::addNewPlaneTimer;
int GameEngine::numOfPlanesInScene = 0;
int GameEngine::maxNumberOfPlanes = 0;

bool GameEngine::startNextLevel()
{
    // Start from the 1st level
    this->currentLevelIndex++;
    std::cout << "Starting game level "
              << this->currentLevelIndex
              << std::endl;
    if (!LevelManager::instance()->createLevel(this->currentLevelIndex)) {
       return false;
    }

    // Setup plane creation timer
    QObject::connect(&(this->addNewPlaneTimer), SIGNAL(timeout()),
                     this, SLOT(addNewPlane()));
    this->addNewPlaneTimer.start(LevelManager::instance()->
                                               getCurrentLevel()->
                                               getNewPlaneInterval());

    // Setup the max number of planes
    this->maxNumberOfPlanes = LevelManager::instance()->
                                            getCurrentLevel()->
                                            getMaxNumberOfPlanes();

    // All OK
    return true;
}

void GameEngine::addNewPlane()
{
    //std::cout << "Adding new plane timer tick ... " << std::endl;

    if (!(this->numOfPlanesInScene < this->maxNumberOfPlanes)) {
        return;
    }

    // FOR NOW:
    // Test with the departure path from runway 0
    // TODO:
    // Random selection of run way

    // Random selection of direction
    bool addDeparturePlane = true;
    if (qrand() % 100 < 50) {
        addDeparturePlane = false;
    }

    if (addDeparturePlane) {

        std::cout << "Adding new departuing plane ... " << std::endl;

        // Plane
        Plane * plane = PlaneModel::instance()->getPlaneItem();
        Q_CHECK_PTR(plane);

        // Plane path
        PlaneDirection * departure = LevelManager::instance()->
                                          getCurrentLevel()->
                                          getRunWay(0)->
                                          getDeparture();
        Q_CHECK_PTR(departure);

        // Pilot
        Pilot * pilot = new TakeOffPilot(plane, departure);
        Q_CHECK_PTR(pilot);
        QObject::connect(pilot, SIGNAL(pilotFinished(Pilot*, Plane*)),
                         this, SLOT(takeOffPilotFinished(Pilot*, Plane*)));

        // Register the plane and the pilot
        this->registerCreationTime(pilot, plane);

        // Hand-off control to the pilot
        pilot->takeControl();
        //pilot->processCommand(new QAction("takeoff", this));
    } else {

        std::cout << "Adding new arriving plane ... " << std::endl;

        // Plane
        Plane * plane = PlaneModel::instance()->getPlaneItem();
        Q_CHECK_PTR(plane);

        // Plane path
        PlaneDirection * arrival = LevelManager::instance()->
                                        getCurrentLevel()->
                                        getRunWay(0)->
                                        getArrival();
        Q_CHECK_PTR(arrival);

        // Pilot
        Pilot * pilot = new LandingPilot(plane, arrival);
        Q_CHECK_PTR(pilot);
        QObject::connect(pilot, SIGNAL(pilotFinished(Pilot*, Plane*)),
                         this, SLOT(landingPilotFinished(Pilot*, Plane*)));

        // Register the plane and the pilot
        this->registerCreationTime(pilot, plane);

        // Hand-off control to the pilot
        pilot->takeControl();
    }

}

void GameEngine::takeOffPilotFinished(Pilot* pilot, Plane * plane)
{
    std::cout << "Engine recieved takeoff pilot finished ..."
              << std::endl
              << "Cleaning after takeoff pilot ..."
              << std::endl;

    // Clean after the pilot and its plane
    QObject::disconnect(pilot, SIGNAL(pilotFinished(Pilot*, Plane*)),
                        this, SLOT(takeOffPilotFinished(Pilot*, Plane*)));
    this->unregisterCreationTime(plane);
    plane->deleteLater();
    pilot->deleteLater();
}

void GameEngine::landingPilotFinished(Pilot* pilot, Plane * plane)
{
    std::cout << "Engine recieved landing pilot finished ..."
              << std::endl
              << "Cleaning after landing pilot ..."
              << std::endl;

    // Clean after the pilot and its plane
    QObject::disconnect(pilot, SIGNAL(pilotFinished(Pilot*, Plane*)),
                        this, SLOT(landingPilotFinished(Pilot*, Plane*)));
    this->unregisterCreationTime(plane);
    plane->deleteLater();
    pilot->deleteLater();
}

void GameEngine::movingPlane()
{
    QList<QTime> creationTimes = this->timesToPlanes.keys();
    Plane * testerPlane;
    Plane * testedPlane;
    Pilot * colliderPilot;
    Pilot * collidedPilot;
    QList<Pilot *> collidingPilots = QList<Pilot *>();
    int sumCollisionDegree;
    int i, j;

    // TODO: Optimize this loop
    for (i=0; i<creationTimes.size(); i++) {
        testerPlane = this->timesToPlanes.value(creationTimes.at(i));
        for (j=i+1; j<creationTimes.size(); j++) {
            sumCollisionDegree = 0;
            testedPlane = this->timesToPlanes.value(creationTimes.at(j));
            if (testerPlane->collidesWithItem(testedPlane, Qt::IntersectsItemBoundingRect)) {
                std::cout << "Collision detected ..."
                          << std::endl;
                colliderPilot = this->timesToPilots.value(creationTimes.at(i));
                collidedPilot = this->timesToPilots.value(creationTimes.at(j));
                sumCollisionDegree =
                        colliderPilot->currentManueverCollisionDegree() +
                        collidedPilot->currentManueverCollisionDegree();
                if (sumCollisionDegree > 2) {
                    if (!collidingPilots.contains(colliderPilot)) {
                        collidingPilots.append(colliderPilot);
                    }
                    if (!collidingPilots.contains(collidedPilot)) {
                        collidingPilots.append(collidedPilot);
                    }
                } else if (sumCollisionDegree > 0) {
                  // Immediate handling of possible plane stopping
                  colliderPilot->handlePlaneStopping();
                  collidedPilot->handlePlaneStopping();
                }
            }
        }
    }

    for (i=0; i<collidingPilots.size(); i++) {
        collidingPilots.at(i)->handlePlaneCollision();
    }
}

void GameEngine::registerCreationTime(Pilot * pilot, Plane * plane)
{
    std::cout << "Registering plane: "
              << plane->getCreationTime().toString(QString("hh:mm:ss.zzz")).toStdString()
              << std::endl;
    this->timesToPlanes.insert(plane->getCreationTime(), plane);
    this->timesToPilots.insert(plane->getCreationTime(), pilot);
    QObject::connect(plane, SIGNAL(moving()),
                     this, SLOT(movingPlane()));
    this->numOfPlanesInScene++;
}

void GameEngine::unregisterCreationTime(Plane * plane)
{
    std::cout << "Un-registering plane: "
              << plane->getCreationTime().toString(QString("hh:mm:ss.zzz")).toStdString()
              << std::endl;
    this->timesToPlanes.remove(plane->getCreationTime());
    this->timesToPilots.remove(plane->getCreationTime());
    QObject::disconnect(plane, SIGNAL(moving()),
                        this, SLOT(movingPlane()));
    this->numOfPlanesInScene--;
}
