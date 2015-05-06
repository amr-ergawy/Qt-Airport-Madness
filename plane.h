#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsProxyWidget>
#include <QList>
#include <QGraphicsItem>
#include <QTime>

#include <iostream>

#include "gamescene.h"

class Plane : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
   Plane(const QPixmap & pixmap);
   QTime getCreationTime();
   void setCommandMenuProxy(QGraphicsProxyWidget * commandMenuProxy);

   QRectF boundingRect() const;
   QPainterPath shape() const;

   void setPos(const QPointF & pos);
   void setPos(qreal x,qreal y);

   ~Plane();

public slots:
   void selectionChanged();
   void positionChanged();

signals:
    void moving();

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent * event);

   
private:
   QGraphicsProxyWidget *  commandMenuProxy;
   QGraphicsColorizeEffect *effect;
   QTime creationTime;
};

#endif // PLANE_H
