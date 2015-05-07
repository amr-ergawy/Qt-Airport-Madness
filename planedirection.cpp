#include "planedirection.h"

PlaneDirection::PlaneDirection()
{
}

void PlaneDirection::addManeuverDescription(ManeuverDescription * maneuverDescription)
{
    this->namesToManeuverDescriptions.insert(*maneuverDescription->getName(),
                                             maneuverDescription);
}

bool PlaneDirection::addManeuverSegment(int index, ManeuverSegment * maneuverSegment)
{
    if (index == 0) {
        QLine * firstLine = maneuverSegment->firstLine();
        if (firstLine == NULL) {
            return false;
        }
        this->originPos = new QPoint(firstLine->p1());
        Q_CHECK_PTR(this->originPos);
        this->originAngle = QLineF(*firstLine).angle();
    }
    this->maneuverSegments.insert(index, maneuverSegment);
    return true;
}

bool PlaneDirection::resolveSegmentsCrossReferences()
{
    for (int i=0; i<this->maneuverSegments.size(); i++) {
        if (!this->maneuverSegments.at(i)->resolveReferences(this->maneuverSegments)) {
            return false;
        }
    }
    return true;
}

QPoint * PlaneDirection::getOriginPos()
{
    return this->originPos;
}

qreal PlaneDirection::getOriginAngle()
{
    return this->originAngle;
}

QSequentialAnimationGroup * PlaneDirection::getManeuver(Plane * plane, QString maneuverName)
{
    QSequentialAnimationGroup * maneuver = new QSequentialAnimationGroup();
    Q_CHECK_PTR(maneuver);
    ManeuverDescription * maneuverDecription =
            this->namesToManeuverDescriptions.value(maneuverName);
    if (maneuverDecription == NULL) {
        return NULL;
    }

    //std::cout << "Direction got maneuver description ..."
    //        << std::endl;

    QVector<int> * maneuverSegmentIndices = maneuverDecription->getSegmentsIndices();
    QPropertyAnimation * maneuverSegementAnmiation;
    int segmentIndex;
    for (int i=0; i<maneuverSegmentIndices->size(); i++) {
        segmentIndex = maneuverSegmentIndices->at(i);
        maneuverSegementAnmiation =
                this->maneuverSegments.at(segmentIndex)->animation();
        if (maneuverSegementAnmiation == NULL) {
            return NULL;
        }

        //std::cout << "Direction got maneuver segment animation ..."
        //        << std::endl;

        maneuverSegementAnmiation->setTargetObject(plane);
        // Leaving disconnections to objects destruction
        QObject::connect(maneuverSegementAnmiation, SIGNAL(valueChanged(const QVariant &)),
                         plane, SLOT(positionChanged()));
        maneuver->addAnimation(maneuverSegementAnmiation);
    }

    //std::cout << "Direction returning maneuver animation ..."
    //          << std::endl;
    maneuver->setObjectName(maneuverName);
    return maneuver;
}

PlaneDirection::~PlaneDirection()
{
    delete this->originPos;
}
