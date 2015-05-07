#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDomElement>
#include <QPoint>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <iostream>

#include "planedirection.h"
#include "linemaneuversegment.h"
#include "beziermaneuversegment.h"
#include "anglemaneuversegment.h"
#include "gamelevel.h"
#include "runway.h"

class LevelManager
{
public:
    static LevelManager *instance (QGraphicsView * gameView=NULL)
    {
        if (m_instance == 0)
          m_instance = new LevelManager(gameView);
        return (m_instance);
    }

    bool createLevel(int i);

    GameLevel * getCurrentLevel();
    QGraphicsScene * getLevelScene();

    ~LevelManager ()
    {
        m_instance = 0;
    }

private:
    LevelManager(QGraphicsView * gameView)
    {
        this->gameView = gameView;
    }

    static LevelManager *m_instance;
    static QGraphicsView *gameView;
    static GameLevel *currentLevel;

    bool parseLevelFile(QIODevice *device);
    RunWay * initializeRunway(const QDomElement &runWayElement);
};

#endif // LEVELMANAGER_H
