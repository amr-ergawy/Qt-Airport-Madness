#include "gamescene.h"

GameScene::GameScene()
{
}

void GameScene::commandMenuTrigger()
{
    std::cout << "Scene menu hiding"
              << std::endl;
    this->clearSelection();
    this->update();
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    QPointF pos = mouseEvent->scenePos();
    std::cout << "Scene mouse press event "
              << pos.x() << " ," << pos.y()
              << std::endl;
    QGraphicsScene::mousePressEvent(mouseEvent);
}

/*
GameScene::GameScene()
{

}
*/

