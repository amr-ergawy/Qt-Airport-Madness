#include "beziermaneuveranimation.h"

BezierManeuverAnimation::BezierManeuverAnimation(QPoint * start, QPoint * key1,
                                                  QPoint * key2, QPoint * end)
{
    path = QPainterPath();
    path.moveTo(QPointF(*start));
    path.cubicTo(QPointF(*key1), QPointF(*key2), QPointF(*end));
    this->setPropertyName("pos");
    this->setStartValue(QPointF(*start));
    this->setEndValue(QPointF(*end));
}

void BezierManeuverAnimation::updateCurrentTime(int currentTime)
{
    /*std::cout << "Bezier anmiation received update-current-time: "
              << currentTime
              << std::endl;*/

    // FROM THE SDK ANIMATION EASING CURVE EXAMPLE
    int duration = this->duration();
    const qreal progress =
                ((duration == 0) ? 1 : ((((currentTime - 1) % duration) + 1) / qreal(duration)));

    qreal easedProgress = easingCurve().valueForProgress(progress);
    if (easedProgress > 1.0) {
        easedProgress -= 1.0;
    } else if (easedProgress < 0) {
        easedProgress += 1.0;
    }
    QPointF point = path.pointAtPercent(easedProgress);
    updateCurrentValue(point);

    /*std::cout << "Bezier anmiation updated current value ..."
              << std::endl;*/

    emit valueChanged(point);
}

