#include <QApplication>
#include <QGraphicsView>

#include "mainwindow.h"
#include "gamescene.h"

#include <iostream>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // Application
    QApplication game(argc, argv);

    // Initiazlise Graphics scene
    std::cout << "Initializing scene ..." << std::endl;
    GameScene gameScene;
    gameScene.setSceneRect(0, 0, 800, 480);
    gameScene.setItemIndexMethod(QGraphicsScene::NoIndex);

    // Initialize Graphics view
    std::cout << "Initializing view ..." << std::endl;
    QGraphicsView gameView(&gameScene);
    gameView.setRenderHint(QPainter::Antialiasing);
    gameView.setCacheMode(QGraphicsView::CacheBackground);
    gameView.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    gameView.setDragMode(QGraphicsView::NoDrag);
    gameView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView.setFixedSize(800, 480);
    gameView.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Airport Madness Qt"));
    gameView.show();

    // Run the application.
    return game.exec();
}
