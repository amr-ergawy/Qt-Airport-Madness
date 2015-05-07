#include "takeoffpilot.h"

TakeOffPilot::TakeOffPilot(Plane * plane, PlaneDirection * planeDirection) :
        Pilot(plane, planeDirection)
{
    this->commandsList.append(QString ("taxi"));
    this->commandsList.append(QString ("lineup"));
    this->commandsList.append(QString ("takeoff"));
    this->commandsList.append(QString ("move"));

    this->maneuversToCollisionDegree.insert(QString ("taxi"), 0);
    this->maneuversToCollisionDegree.insert(QString ("lineup"), 1);
    this->maneuversToCollisionDegree.insert(QString ("takeoff"), 2);

    this->maneuversToStoppable.insert(QString ("taxi"), true);
    this->maneuversToStoppable.insert(QString ("lineup"), false);
    this->maneuversToStoppable.insert(QString ("takeoff"), false);

    this->lastScheduledIndex = -1;

    this->currentCollisionDegree = 0;
    this->currentStoppableFlag = true;
}

void TakeOffPilot::startNextManeuver()
{
    this->currentManeuver = NULL;
    if (!this->scheduledManeuvers.isEmpty()) {

        int commandIndex= this->scheduledManeuvers.begin().key();
        this->currentCommandIndex = commandIndex;
        this->currentManeuver = this->scheduledManeuvers.take(commandIndex);
        QObject::connect(this->currentManeuver, SIGNAL(finished()),
                         this, SLOT(maneuverFinished()));

        QString maneuverName = this->currentManeuver->objectName();
        this->currentCollisionDegree =
                this->maneuversToCollisionDegree.value(maneuverName);
        this->currentStoppableFlag =
                this->maneuversToStoppable.value(maneuverName);

        std::cout << "TakeOff Pilot starting maneuver ... "
                  << std::endl;
        this->currentManeuver->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void TakeOffPilot::maneuverFinished()
{
    QString finishedManeuverName = QString(this->currentManeuver->objectName());
    std::cout << "Take-off pilot finished maneuver: "
              << finishedManeuverName.toStdString()
              << std::endl;

    if (this->currentManeuver != NULL) {
        QObject::disconnect(this->currentManeuver, SIGNAL(finished()),
                            this, SLOT(maneuverFinished()));
        // Assuming that the children maneuver objects will be deleted
        this->currentManeuver->deleteLater();
    }
    if (this->currentCommandIndex == this->commandsList.indexOf("takeoff")) {
        this->cleanAfterPlane();
        emit pilotFinished(this, this->plane);
    } else {
        this->startNextManeuver();
    }
}

bool TakeOffPilot::processCommand(QAction * action)
{
    // TODO: remove state printing after testing
     std::cout << "Take off pilot maneuver state: ";
     if (this->currentManeuver != NULL) {
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
    }

    std::cout << "Takoff pilot received command: "
              << action->text().toStdString()
              << std::endl;

    int commandIndex = this->commandsList.indexOf(action->text());
    //std::cout << "Command index: "
    //          << commandIndex
    //          << std::endl;

    std::cout << "Takoff pilot processing command ... "
              << std::endl;

    if (commandIndex == this->commandsList.indexOf("move")) {
        if (this->currentManeuver != NULL &&
            this->currentManeuver->state() == QAbstractAnimation::Paused) {
            std::cout << "Takoff pilot resuming paused maneuver ... "
                      << std::endl;
            this->currentManeuver->resume();
        }
    } else {
        // Schedule command if not yet scheduled
        if (this->lastScheduledIndex < commandIndex) {

            int indexDiff = commandIndex - this->lastScheduledIndex;
            int toScheduleIndex;
            QString toScheduleManeuverName;

            for (int i=1; i<=indexDiff; i++) {

                toScheduleIndex = this->lastScheduledIndex + i;
                QSequentialAnimationGroup * maneuver;

                if (this->suspendedManeuvers.contains(toScheduleIndex)) {

                    maneuver = this->suspendedManeuvers.take(toScheduleIndex);

                } else {

                    toScheduleManeuverName = this->commandsList.at(toScheduleIndex);
                    maneuver = this->planeDirection->
                                     getManeuver(this->plane,
                                                 toScheduleManeuverName);
                    if (maneuver == NULL) {
                        std::cout << "Got NULL animation ... "
                                  << std::endl;
                        return false;
                    }
                }

                std::cout << "Takoff pilot scheduling maneuver "
                          << toScheduleManeuverName.toStdString()
                          << std::endl;

                this->scheduledManeuvers.insert(toScheduleIndex, maneuver);
            }

            this->lastScheduledIndex = commandIndex;

        } else if (this->lastScheduledIndex > commandIndex &&
                   this->currentCommandIndex <= commandIndex) {
            int indexDiff = this->lastScheduledIndex - commandIndex;
            int toSuspendIndex;

            for (int i=1; i<=indexDiff; i++) {

                toSuspendIndex = commandIndex + i;

                if (this->scheduledManeuvers.contains(toSuspendIndex)) {

                    std::cout << "Takoff pilot suspending maneuver "
                              << this->commandsList.at(toSuspendIndex).toStdString()
                              << std::endl;

                    QSequentialAnimationGroup * maneuver =
                            this->scheduledManeuvers.take(toSuspendIndex);
                    this->suspendedManeuvers.insert(toSuspendIndex, maneuver);
                }
            }

            this->lastScheduledIndex = commandIndex;
        }

        if (this->currentManeuver == NULL) {
            this->startNextManeuver();
        }
    }


    return true;
}
