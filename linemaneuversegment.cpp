#include "linemaneuversegment.h"

LineManeuverSegment::LineManeuverSegment(QPoint * start,
                                         QPoint * end)
    : ManeuverSegment()
{
    this->line = new QLine(*start, *end);
}

QLine * LineManeuverSegment::firstLine()
{
    return this->line;
}

QLine * LineManeuverSegment::lastLine()
{
    return this->line;
}

QPropertyAnimation * LineManeuverSegment::animation()
{
    //std::cout << "Line creating animation ..."
    //          << std::endl;
    QPropertyAnimation * animation = new LineManeuverAnimation();
    Q_CHECK_PTR(animation);
    animation->setPropertyName("pos");
    animation->setStartValue(this->line->p1());
    animation->setEndValue(this->line->p2());
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setLoopCount(1);
    animation->setDuration(5000);
    //std::cout << "Line returning animation ..."
    //          << std::endl;
    return animation;
}

LineManeuverSegment::~LineManeuverSegment()
{
    delete this->line;
}
