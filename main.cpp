#include "chess.h"

#include "Game.h"

#include <QApplication>

#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {

    QApplication a(argc, argv);
    MainWindow w;

    Game game(Game::NORMAL, & w);

    game.start();
    w.initUI();
    w.show();

    return a.exec();

}
