#ifndef MANEUVERDESCRIPTION_H
#define MANEUVERDESCRIPTION_H

#include <QString>
#include <QMap>

#include "maneuversegment.h"

class ManeuverDescription
{
public:
    ManeuverDescription(QString * name);
    QString * getName();
    void addManeuverSegmentIndex(int segmentIndex);
    QVector<int> * getSegmentsIndices();
    ~ManeuverDescription();

private:
    QString * name;
    QVector<int> maneuverSegmentsIndices;
};

#endif // MANEUVERDESCRIPTION_H
