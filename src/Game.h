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
#include <vector>

#include "Player.h"

class Game {
    public:
        enum Mode {
            NORMAL,
            CHESS960,
            RANDOM
        };



    Game(Mode mode, MainWindow * mw, int playerone, int playertwo);

    virtual~Game();
    MainWindow * getWindow();

    void start();
    Board * getBoard();
    void drawPieces();
    void refreshPieces();
    void showPieceMoves(Piece * currPiece);
    void clearPieceMoves();
    void movePiece(Piece * piece, int square);
    void changeTurn();
    bool isActive();
    private:
        Board * board;
    MainWindow * mw;

    Player* player1;
    Player* player2;
    bool active;
    QImage image;

};

#endif /* GAME_H_ */
