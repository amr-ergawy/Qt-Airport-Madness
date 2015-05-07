#ifndef PLANEDIRECTION_H
#define PLANEDIRECTION_H

#include <QPoint>
#include <QString>
#include <QMap>
#include <QLineF>
#include <QtGlobal>
#include <QSequentialAnimationGroup>
#include <QVector>
#include <QPropertyAnimation>

#include <iostream>

#include "maneuverdescription.h"
#include "plane.h"

class PlaneDirection
{
public:
    PlaneDirection();
    void addManeuverDescription(ManeuverDescription * maneuverDescription);
    bool addManeuverSegment(int index, ManeuverSegment * maneuverSegment);
    bool resolveSegmentsCrossReferences();
    QPoint * getOriginPos();
    qreal getOriginAngle();
    QSequentialAnimationGroup * getManeuver(Plane * plane, QString maneuverName);
    ~PlaneDirection();

protected:
    QMap<QString, ManeuverDescription *> namesToManeuverDescriptions;
    QVector<ManeuverSegment *> maneuverSegments;
    QPoint * originPos;
    qreal originAngle;
};

#endif // PLANEDIRECTION_H
