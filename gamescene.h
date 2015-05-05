#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QString>

#include <iostream>

class GameScene : public QGraphicsScene
{
Q_OBJECT

public:
    GameScene();

public slots:
    void commandMenuTrigger();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

/*
class GameScene
{
public:
    GameScene();
};
*/

#endif // GAMESCENE_H
