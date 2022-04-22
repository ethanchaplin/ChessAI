#include "chess.h"

#include "Game.h"

#include <QApplication>

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char * argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    std::map<std::string, int> types= {{"human", 0}, {"robot", 1}, {"smooth", 2}};

    Game game(Game::NORMAL, & w, types.at(argv[1]), types.at(argv[2]));






    w.initUI();
    w.show();

    game.start();


    return a.exec();

}

