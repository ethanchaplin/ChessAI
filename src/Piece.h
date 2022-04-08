/*
 * Piece.h
 *
 *  Created on: Mar 30, 2022
 *      Author: coold
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

class Piece {

    public:
        enum Color {
            BLACK,
            WHITE
        };
    enum Type {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        KING,
        QUEEN
    };

    Piece(Color color, Type type, int pos);
    virtual~Piece();
    void move(int square);

    Type getType();
    Color getColor();
    void setXPos(int x);
    void setYPos(int y);
    void setCompositePosition(int pos);
    int getXPos();
    int getYPos();
    int getCompositePosition();
    std::vector < int > getLegalMoves();
    void populateLegalMoves(std::vector < int > moves);

    bool hasPreviouslyMoved();
    private:
        Color color;
    Type type;
    int pos;
    std::vector < int > legalMoves;
    bool hasMoved = false;
};

#endif /* PIECE_H_ */
