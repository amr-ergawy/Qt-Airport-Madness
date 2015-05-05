#include <QApplication>

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

    MainWindow w;
    w.show();

    // return a.exec();
    return game.exec();
}
