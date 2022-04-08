/*
 * Game.h
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>

#include "Board.h"

#include <QApplication>

#include "qgraphicsscene.h"

#include "qgraphicsview.h"

#include "chess.h"

class Game {
    public:
        enum Mode {
            NORMAL,
            CHESS960,
            RANDOM
        };
    Game(Mode mode, MainWindow * mw);

    virtual~Game();
    MainWindow * getWindow();

    void start();
    Board * getBoard();
    void drawPieces();
    private:
        Board * board;
    MainWindow * mw;
};

#endif /* GAME_H_ */
