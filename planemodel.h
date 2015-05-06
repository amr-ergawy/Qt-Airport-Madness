#ifndef PLANEMODEL_H
#define PLANEMODEL_H

#include <QBitmap>
#include <QPixmap>
#include <QDir>
#include <QString>

#include "plane.h"

class PlaneModel
{
public:
    static PlaneModel *instance (QString planePixmapFile=NULL)
    {
        if (m_instance == 0)
          m_instance = new PlaneModel(planePixmapFile);
        return (m_instance);
    }

    Plane * getPlaneItem();

    ~PlaneModel ()
    {
        m_instance = 0;
    }

private:
    PlaneModel(QString planePixmapFile);

    static PlaneModel *m_instance;
    QPixmap planePixmap;
};

#endif // PLANEMODEL_H
