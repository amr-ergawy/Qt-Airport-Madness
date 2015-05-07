#include "anglemaneuversegment.h"

AngleManeuverSegment::AngleManeuverSegment(int startIndex,
                                           int endIndex)
    : ManeuverSegment()
{
    this->startIndex = startIndex;
    this->endIndex = endIndex;
}

bool AngleManeuverSegment::resolveReferences(QVector<ManeuverSegment *> directionSegments)
{
    if (!(this->startIndex < directionSegments.size() &&
          this->endIndex < directionSegments.size())) {
        return false;
    }

    ManeuverSegment * startLineSegment = directionSegments.at(this->startIndex);
    ManeuverSegment * endLineSegment = directionSegments.at(this->endIndex);

    if (startLineSegment == NULL ||
        endLineSegment == NULL) {
        return false;
    }

    std::cout << "Angle segment: Resolving references ..."
              << std::endl;

    return true;
}
