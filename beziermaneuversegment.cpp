#include "beziermaneuversegment.h"

BezierManeuverSegment::BezierManeuverSegment(QPoint * start,
                                             QPoint * key1,
                                             QPoint * key2,
                                             QPoint * end)
    : ManeuverSegment()
{
    this->start = start;
    this->key1 = key1;
    this->key2 = key2;
    this->end = end;
}

QLine * BezierManeuverSegment::firstLine()
{
    return new QLine(*this->start, *this->key1);
}

QPropertyAnimation * BezierManeuverSegment::animation()
{
    //std::cout << "Bezier creating animation ..."
    //          << std::endl;
    QPropertyAnimation * animation =
            new BezierManeuverAnimation(start, key1, key2, end);
    Q_CHECK_PTR(animation);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setLoopCount(1);
    animation->setDuration(5000);
    //std::cout << "Bezier returning animation ..."
    //          << std::endl;
    return animation;
}

BezierManeuverSegment::~BezierManeuverSegment()
{
    delete this->start;
    delete this->key1;
    delete this->key2;
    delete this->end;
}
