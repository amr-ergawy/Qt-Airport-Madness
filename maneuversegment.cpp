#include "maneuversegment.h"

ManeuverSegment::ManeuverSegment()
{
}

QLine * ManeuverSegment::firstLine()
{
    return NULL;
}

QLine * ManeuverSegment::lastLine()
{
    return NULL;
}

bool ManeuverSegment::resolveReferences(QVector<ManeuverSegment *> directionSegment)
{
    if (directionSegment.isEmpty()) {
        return false;
    }
    return true;
}

QPropertyAnimation * ManeuverSegment::animation()
{
    return NULL;
}

ManeuverSegment::~ManeuverSegment()
{
}
