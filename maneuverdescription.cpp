#include "maneuverdescription.h"

ManeuverDescription::ManeuverDescription(QString * name)
{
    this->name = name;
}

QString * ManeuverDescription::getName()
{
    return this->name;
}

void ManeuverDescription::addManeuverSegmentIndex(int segmentIndex)
{
    this->maneuverSegmentsIndices.append(segmentIndex);
}

QVector<int> * ManeuverDescription::getSegmentsIndices()
{
    return &(this->maneuverSegmentsIndices);
}

ManeuverDescription::~ManeuverDescription()
{
    delete this->name;
}
