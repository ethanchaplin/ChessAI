/*
 * Board.h
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Piece.h"

class Board {
    public:
        enum Turn {
            T_WHITE,
            T_BLACK
        };

    Board();
    Piece * getPiece(int pos);
    Piece ** getPieces();

    void setPiece(int pos, Piece * piece);
    virtual~Board();
    void computeAllPiecesLegalMove();
    Turn getTurn();
    void changeTurn();
    void addCheckMoves(Piece::Color attackingPiece, int pos);

    private:
        Piece * pieceLocations[64];
    Turn turn = T_WHITE;

    std::vector < int > wCheckMoves;
    std::vector < int > bCheckMoves;

};

#endif /* BOARD_H_ */
