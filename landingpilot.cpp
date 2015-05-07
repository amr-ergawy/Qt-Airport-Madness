#include "landingpilot.h"

LandingPilot::LandingPilot(Plane * plane, PlaneDirection * planeDirection) :
        Pilot(plane, planeDirection)
{
    this->commandsList.append(QString ("land"));
    this->commandsList.append(QString ("around"));
    this->commandsList.append(QString ("move"));

    this->maneuversToCollisionDegree.insert(QString ("land"), 2);
    this->maneuversToCollisionDegree.insert(QString ("around"), 0);
    this->maneuversToCollisionDegree.insert(QString ("approach"), 0);
    this->maneuversToCollisionDegree.insert(QString ("taxi"), 0);

    this->maneuversToStoppable.insert(QString ("land"), false);
    this->maneuversToStoppable.insert(QString ("around"), false);
    this->maneuversToStoppable.insert(QString ("approach"), false);
    this->maneuversToStoppable.insert(QString ("taxi"), true);

    this->stillApproaching = false;
    this->nextManeuver = NULL;

    this->currentCollisionDegree = 0;
    this->currentStoppableFlag = false;
}

void LandingPilot::startNextManeuver()
{    
    this->currentManeuver = this->nextManeuver;

    QString maneuverName = this->currentManeuver->objectName();
    this->currentCollisionDegree =
            this->maneuversToCollisionDegree.value(maneuverName);
    this->currentStoppableFlag =
            this->maneuversToStoppable.value(maneuverName);

    std::cout << "Landing pilot starting next maneuver ... "
              << std::endl;    
    QObject::connect(this->currentManeuver, SIGNAL(finished()),
                     this, SLOT(maneuverFinished()));
    this->currentManeuver->start();
}

void LandingPilot::maneuverFinished()
{
    QString finishedManeuverName = QString(this->currentManeuver->objectName());
    std::cout << "Landing pilot finished maneuver: "
              << finishedManeuverName.toStdString()
              << std::endl;

    if (this->currentManeuver != NULL) {
        QObject::disconnect(this->currentManeuver, SIGNAL(finished()),
                            this, SLOT(maneuverFinished()));
        // Assuming that the children maneuver objects will be deleted
        this->currentManeuver->deleteLater();
    }
    if (this->stillApproaching) {
        this->stillApproaching = false;
        this->startNextManeuver();
    } else if (finishedManeuverName.operator ==("land")) {
        this->nextManeuver = this->taxiManeuver;
        this->startNextManeuver();
    } else {
        this->cleanAfterPlane();
        emit pilotFinished(this, this->plane);
    }
}

bool LandingPilot::processCommand(QAction * action)
{
    // TODO: remove state printing after testing
     std::cout << "Landing pilot maneuver state: ";
    switch (this->currentManeuver->currentAnimation()->state()) {
    case QAbstractAnimation::Stopped:
        std::cout << "Stopped: ";
        break;
    case QAbstractAnimation::Paused:
        std::cout << "Paused: ";
        break;
    case QAbstractAnimation::Running:
        std::cout << "Running: ";
        break;
    }
    std::cout << this->currentManeuver->currentAnimation()->currentTime()
              << std::endl;

    std::cout << "Landing pilot received command: "
              << action->text().toStdString()
              << std::endl;

    if (action->text().operator ==("move")) {
        if (this->currentManeuver != NULL &&
            this->currentManeuver->state() == QAbstractAnimation::Paused) {
            std::cout << "Landing pilot resuming paused maneuver ... "
                      << std::endl;
            this->currentManeuver->resume();
        }
    } else {
        if (this->stillApproaching) {
            if (action->text().operator ==("land")) {
                this->nextManeuver = this->landManeuver;
            }
            if (action->text().operator ==("around")) {
                this->nextManeuver = this->aroundManeuver;
            }
            std::cout << "Landing pilot configured next maneuver "
                      << std::endl;
        }
    }
    return true;
}


void LandingPilot::initPlane()
{
    Pilot::initPlane();

    std::cout << "Landing pilot getting approach maneuver ... "
              << std::endl;

    this->landManeuver =
            this->planeDirection->getManeuver(this->plane, "land");
    this->nextManeuver = this->landManeuver;

    this->aroundManeuver =
            this->planeDirection->getManeuver(this->plane, "around");

    this->taxiManeuver =
            this->planeDirection->getManeuver(this->plane, "taxi");

    QSequentialAnimationGroup * approachManeuver =
            this->planeDirection->getManeuver(this->plane, "approach");

    if (approachManeuver == NULL ||
        this->landManeuver == NULL ||
        this->aroundManeuver == NULL ||
        this->landManeuver == NULL) {
        std::cout << "Landing pilot got NULL animation ... "
                  << std::endl;
        emit pilotFinished(this, this->plane);
        return;
    }

    std::cout << "Landing pilot starting to approach "
              << std::endl;
    this->stillApproaching = true;
    this->currentManeuver = approachManeuver;
    QObject::connect(approachManeuver, SIGNAL(finished()),
                     this, SLOT(maneuverFinished()));
    approachManeuver->start();
}
