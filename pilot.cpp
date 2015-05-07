#include "pilot.h"

Pilot::Pilot(Plane * plane, PlaneDirection * planeDirection)
{
    this->plane = plane;
    this->planeDirection = planeDirection;
    this->currentManeuver = NULL;

    commandMenu = new QMenu();
    Q_CHECK_PTR(commandMenu);
}

void Pilot::takeControl()
{
    this->initPlane();
}

int Pilot::currentManueverCollisionDegree()
{
    return this->currentCollisionDegree;
}

void Pilot::handlePlaneCollision()
{
    if (this->currentManeuver != NULL) {
        this->currentManeuver->stop();
        //TODO: Review sub-classes maneuver cleaning
        this->currentManeuver->deleteLater();
    }
    this->cleanAfterPlane();
    emit pilotFinished(this, this->plane);
}

void Pilot::handlePlaneStopping()
{
    if (this->currentStoppableFlag) {
        if (this->currentManeuver != NULL &&
            this->currentManeuver->state() == QAbstractAnimation::Running) {
            this->currentManeuver->pause();
        }
    }
}

bool Pilot::processCommand(QAction * action)
{
 return true;
}

void Pilot::maneuverFinished()
{
    //Next to do after a maneuver is finished
}

void Pilot::initPlane()
{
    QGraphicsScene * gameScene = LevelManager::instance()->getLevelScene();
    gameScene->addItem(this->plane);
    QObject::connect(gameScene, SIGNAL(selectionChanged()),
                     this->plane, SLOT(selectionChanged()));
    this->plane->setPos(this->planeDirection->getOriginPos()->x(),
                        this->planeDirection->getOriginPos()->y());
    //this->plane->setRotation(this->planeDirection->getOriginAngle());

    // Initializing command menu
    for (int i=0; i<commandsList.size(); i++) {
        this->commandMenu->addAction(commandsList.at(i));
    }
    this->commandMenu->setVisible(false);
    this->commandMenuProxy = gameScene->addWidget(this->commandMenu);
    this->commandMenuProxy->setPos(0, 0);
    this->plane->setCommandMenuProxy(this->commandMenuProxy);
    QObject::connect(this->commandMenu, SIGNAL(triggered(QAction*)),
                     gameScene, SLOT(commandMenuTrigger()));
    QObject::connect(this->commandMenu, SIGNAL(triggered(QAction*)),
                     this, SLOT(processCommand(QAction*)));
}

void Pilot::cleanAfterPlane()
{
    QGraphicsScene * gameScene = LevelManager::instance()->getLevelScene();
    if (this->plane->isSelected()) {
        gameScene->clearSelection();
    }
    QObject::disconnect(gameScene, SIGNAL(selectionChanged()),
                        this->plane, SLOT(selectionChanged()));
    QObject::disconnect(this->commandMenu, SIGNAL(triggered(QAction*)),
                        gameScene, SLOT(commandMenuTrigger()));
    QObject::disconnect(this->commandMenu, SIGNAL(triggered(QAction*)),
                        this, SLOT(processCommand(QAction*)));
    gameScene->removeItem(this->commandMenuProxy);
    gameScene->removeItem(this->plane);
    delete this->commandMenu;
}
