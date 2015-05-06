#include "plane.h"

Plane::Plane(const QPixmap & pixmap) :
    QObject(), QGraphicsPixmapItem(pixmap, 0)
{
    // Shift the transform origin
    setTransformOriginPoint(356/16, 424/16);

    //Add the selection effect
    effect = new QGraphicsColorizeEffect;
    Q_CHECK_PTR(effect);
    effect->setColor(QColor(0, 255, 0));
    effect->setEnabled(true);
    effect->setStrength(0);
    ((QGraphicsPixmapItem *)this)->setGraphicsEffect(effect);

    //Selectble
    this->setFlag(QGraphicsPixmapItem::ItemIsSelectable);

    //Set creation time stamp
    this->creationTime = QTime::currentTime();
}

QTime Plane::getCreationTime()
{
    return this->creationTime;
}

void Plane::setCommandMenuProxy(QGraphicsProxyWidget *  commandMenuProxy)
{
    this->commandMenuProxy = commandMenuProxy;
}

QRectF Plane::boundingRect() const
{
    return QRectF(0, 0,
                  356/8, 424/8);
}

QPainterPath Plane::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Plane::setPos(const QPointF & pos)
{
    Plane::setPos(pos.x(), pos.y());
}

void Plane::setPos(qreal x,qreal y)
{
    QGraphicsPixmapItem::setPos(x-356/16, y-424/16);
}

void Plane::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    std::cout << "mouse press from plane ..."
              << std::endl;
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Plane::selectionChanged()
{
    std::cout << "Plane recieved selection changed ..."
              << std::endl;
    if (this->isSelected()) {
        std::cout << "Plane selected ..."
                  << std::endl;
        this->effect->setStrength(1);
        this->commandMenuProxy->setPos(this->pos().x()+356/16,
                                       this->pos().y()+424/16);
        this->commandMenuProxy->show();
    } else {
        std::cout << "Plane unselected ..."
                  << std::endl;
        this->effect->setStrength(0);
        this->commandMenuProxy->hide();
    }
}

void Plane::positionChanged()
{
    emit moving();
}

Plane::~Plane()
{
    delete this->effect;
}
