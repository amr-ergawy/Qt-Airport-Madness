#ifndef LANDINGPILOT_H
#define LANDINGPILOT_H

#include "pilot.h"

class LandingPilot : public Pilot
{
Q_OBJECT

public:
    LandingPilot(Plane * plane, PlaneDirection * planeDirection);
    void startNextManeuver();

public slots:
    void maneuverFinished();
    bool processCommand(QAction * action);

protected:
    void initPlane();

    QSequentialAnimationGroup * landManeuver;
    QSequentialAnimationGroup * aroundManeuver;
    QSequentialAnimationGroup * taxiManeuver;
    bool stillApproaching;
    QSequentialAnimationGroup * nextManeuver;
};

#endif // LANDINGPILOT_H
