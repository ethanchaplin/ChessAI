/*
 * Game.cpp
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#include "Game.h"


#include <QGraphicsPixmapItem>

#include <iostream>

#include <vector>

#include <string>

#include <algorithm>

#include "PieceItem.h"
Game::Game(Mode mode, MainWindow * mw) {
    board = new Board();
    this -> mw = mw;
    this -> basicScene = new QGraphicsScene();

    switch (mode) {
    case NORMAL:
        board -> setPiece(0, new Piece(Piece::WHITE, Piece::ROOK, 0));
        board -> setPiece(1, new Piece(Piece::WHITE, Piece::KNIGHT, 1));
        board -> setPiece(32, new Piece(Piece::WHITE, Piece::BISHOP, 32));
        board -> setPiece(3, new Piece(Piece::WHITE, Piece::QUEEN, 3));
        //board -> setPiece(4, new Piece(Piece::WHITE, Piece::KING, 4));
        board -> setPiece(5, new Piece(Piece::WHITE, Piece::BISHOP, 5));
        board -> setPiece(6, new Piece(Piece::WHITE, Piece::KNIGHT, 6));
        board -> setPiece(7, new Piece(Piece::WHITE, Piece::ROOK, 7));

        board -> setPiece(8, new Piece(Piece::WHITE, Piece::PAWN, 8));
        board -> setPiece(9, new Piece(Piece::WHITE, Piece::PAWN, 9));

        board -> setPiece(37, new Piece(Piece::WHITE, Piece::KING, 37));

        board -> setPiece(10, new Piece(Piece::WHITE, Piece::PAWN, 10));

        board -> setPiece(11, new Piece(Piece::WHITE, Piece::PAWN, 11));

        board -> setPiece(12, new Piece(Piece::WHITE, Piece::PAWN, 12));
        board -> setPiece(13, new Piece(Piece::WHITE, Piece::PAWN, 13));
        board -> setPiece(14, new Piece(Piece::WHITE, Piece::PAWN, 14));
        board -> setPiece(15, new Piece(Piece::WHITE, Piece::PAWN, 15));

        board -> setPiece(56, new Piece(Piece::BLACK, Piece::ROOK, 56));
        board -> setPiece(57, new Piece(Piece::BLACK, Piece::KNIGHT, 57));
        board -> setPiece(58, new Piece(Piece::BLACK, Piece::BISHOP, 58));

        board -> setPiece(60, new Piece(Piece::BLACK, Piece::KING, 60));
        board -> setPiece(61, new Piece(Piece::BLACK, Piece::BISHOP, 61));
        board -> setPiece(62, new Piece(Piece::BLACK, Piece::KNIGHT, 62));
        board -> setPiece(63, new Piece(Piece::BLACK, Piece::ROOK, 63));

        board -> setPiece(55, new Piece(Piece::BLACK, Piece::PAWN, 55));
        board -> setPiece(54, new Piece(Piece::BLACK, Piece::PAWN, 54));
        board -> setPiece(53, new Piece(Piece::BLACK, Piece::PAWN, 53));
        board -> setPiece(52, new Piece(Piece::BLACK, Piece::PAWN, 52));
        board -> setPiece(51, new Piece(Piece::BLACK, Piece::PAWN, 51));
        board -> setPiece(50, new Piece(Piece::BLACK, Piece::PAWN, 50));
        board -> setPiece(49, new Piece(Piece::BLACK, Piece::PAWN, 49));
        board -> setPiece(48, new Piece(Piece::BLACK, Piece::PAWN, 48));

        break;

    }

}

Game::~Game() {
    delete board;
    delete mw;
    delete basicScene;
}

void Game::start() {

    board -> computeAllPiecesLegalMove();

    drawPieces();

}

Board * Game::getBoard() {
    return board;
}

MainWindow * Game::getWindow() {
    return mw;
}
void Game::initScene(){

}
void Game::drawPieces() {
    QGraphicsScene * scene = basicScene;


    for (int square = 0; square < 64; square++) {
        if (board -> getPieces()[square] != nullptr) {
            std::string name = "";
            std::string color = "";

            Piece * currPiece = board -> getPieces()[square];
            if (currPiece -> getColor() == Piece::WHITE) {
                color = "w";
            } else {
                color = "b";
            }

            switch (currPiece -> getType()) {

            case (Piece::BISHOP):
                name = "b";
                break;
            case (Piece::PAWN):
                name = "p";
                break;
            case (Piece::ROOK):
                name = "r";
                break;
            case (Piece::KNIGHT):
                name = "n";
                break;
            case (Piece::KING):
                name = "k";
                break;
            case (Piece::QUEEN):
                name = "q";
                break;

            }

            QString qstr = QString::fromStdString("C:\\Users\\coold\\Documents\\ChessAI\\assets\\" + name + color + ".png");
            QImage image(qstr);
            image = image.scaled(50, 50);

            QGraphicsPixmapItem * item = new PieceItem(QPixmap::fromImage(image), currPiece, this);
            item -> setFlags({QGraphicsItem::ItemIsSelectable, QGraphicsItem::ItemIsMovable});


            item -> setZValue(10);
            item -> setPos((50 * currPiece -> getXPos()), (50 * currPiece -> getYPos()));
            scene->addItem(item);


        }
    }

    mw->updateUI(basicScene);

}
void Game::showPieceMoves(Piece * currPiece){
    clearPieceMoves();


    for(int i = 0; i < (long)currPiece->getLegalMoves().size(); i++){
        int x = currPiece->getLegalMoves()[i] % 8;
        int y = currPiece->getLegalMoves()[i] / 8;

        QGraphicsEllipseItem * circle = new QGraphicsEllipseItem(12.5, 12.5, 25, 25);

        circle -> setZValue(10);
        circle -> setPos((50 * x), (50 * y));
        circle -> setBrush(QBrush(Qt::black, Qt::BrushStyle::Dense7Pattern));
        basicScene->addItem(circle);
    }
    mw->updateUI(basicScene);
}

void Game::clearPieceMoves(){
    foreach (QGraphicsItem *item, basicScene->items()) {
        QGraphicsEllipseItem *node = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        if (!node) // it was NOT an QGraphicsEllipseItem item, so skip it
            continue;
        else{
          basicScene->removeItem(node); // take it out ( wont delete, see docs)
          delete node; // delete it
    }
        }
    mw->updateUI(basicScene);
}
