#include "planemodel.h"

PlaneModel *PlaneModel::m_instance = 0;

PlaneModel::PlaneModel(QString planePixmapFile)
{
    planePixmap = QPixmap(planePixmapFile);
    planePixmap = planePixmap.scaledToHeight(424/8, Qt::SmoothTransformation);
    planePixmap = planePixmap.scaledToWidth(356/8, Qt::SmoothTransformation);
}

Plane * PlaneModel::getPlaneItem()
{
    Plane * planeItem;
    planeItem = new Plane(PlaneModel::instance()->planePixmap);
    Q_CHECK_PTR(planeItem);
    planeItem->setPos(400, 240);
    return planeItem;
}
